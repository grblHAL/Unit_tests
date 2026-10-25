"""Structured, concise findings shared by stage capture and the final CI report."""
from known_crash import matches_known_crash
import argparse
import html
import json
import os
from pathlib import Path
import re
import xml.etree.ElementTree as ET


def location(text):
    match = re.search(r"((?:[A-Za-z]:)?[^\n]*?(?:core/|tests/|plugins/|drivers/|deps/|scripts/)[^: \n]+):(\d+)(?::\d+)?", text.replace("\\", "/"))
    if not match:
        cmake = re.search(r"(CMakeLists\.txt):(\d+)", text)
        return (cmake[1], int(cmake[2])) if cmake else ("", None)
    path = match[1]
    for prefix in ("core/", "tests/", "plugins/", "drivers/", "deps/", "scripts/"):
        marker = re.search(r"(?:^|/)" + re.escape(prefix), path)
        if marker:
            path = path[marker.end() - len(prefix):]
            break
    return path, int(match[2])


def short_line(line):
    path, number = location(line)
    if path and number:
        line = re.sub(r"^.*?" + re.escape(path) + r":\d+(?::\d+)?:\s*", "", line.replace("\\", "/"))
    return line.strip()[:350]


def concise(text):
    lines = text.splitlines()
    for pattern in ("SUMMARY: AddressSanitizer:", "runtime error:", ": error:", "expected", "CHECK("):
        for line in lines:
            if pattern in line:
                return short_line(line)
    for line in lines:
        if re.search(r"\.[ch]:\d+:", line):
            return short_line(line)
    return next((short_line(line) for line in lines if line.strip()), "No diagnostic emitted; inspect the attached log.")


def finding(kind, name, message, detail="", severity="error"):
    path, line = location(detail or message)
    return dict(kind=kind, name=name, message=message, file=path, line=line, severity=severity)


def build_failure(stage, output):
    lines = output.splitlines()
    primary = next((line for line in lines if re.search(r"(?:fatal )?error:|undefined reference|undefined symbol|CMake Error|Traceback", line)), "")
    if "CMake Error" in primary:
        index = lines.index(primary)
        reason = next((line.strip() for line in lines[index + 1:] if line.strip()), "")
        primary += " " + reason
    if "Traceback" in primary:
        primary = next((line for line in reversed(lines) if re.match(r"[\w.]+(?:Error|Exception):", line)), primary)
    return finding("build" if stage == "build" else "setup", stage, concise(primary or output), primary or output)


def test_findings(path, diagnostics):
    manifest_path = Path(diagnostics) / "known_sanitizer_diagnostics.json"
    manifest = json.loads(manifest_path.read_text()) if manifest_path.exists() else []
    cases = list(ET.parse(path).getroot().iter("testcase"))
    findings = []
    counts = dict(total=len(cases), clean=0, known=0, skipped=0, failed=0)
    for case in cases:
        name = case.get("name", "unknown")
        known = any(p.get("name") == "cmake_labels" and "known_bug" in p.get("value", "").split(";") for p in case.findall("./properties/property"))
        expected_diagnostic = any(p.get("name") == "cmake_labels" and "known_sanitizer_bug" in p.get("value", "").split(";") for p in case.findall("./properties/property"))
        error = next((case.find(tag) for tag in ("failure", "error") if case.find(tag) is not None), None)
        output = "\n".join(case.findtext(tag, "") for tag in ("system-out", "system-err"))
        if case.find("skipped") is not None:
            counts["skipped"] += 1
            continue
        profile_errors = [line for line in output.splitlines() if line.lstrip().startswith(("profiling:", "libgcov profiling error:"))]
        if profile_errors:
            findings.append(finding("coverage", name, "Coverage counter data could not be saved; check writable output paths and rerun coverage.", "\n".join(profile_errors)))
            counts["failed"] += 1
            continue
        unexpected = []
        fatal = any(p.get("name") == "cmake_labels" and "known_crash" in p.get("value", "").split(";") for p in case.findall("./properties/property"))
        expected_diagnostic = expected_diagnostic or fatal
        if error is None and not (fatal and matches_known_crash(name, output, manifest)):
            for line in output.splitlines():
                if "runtime error:" not in line and "ERROR: AddressSanitizer" not in line:
                    continue
                m = re.match(r"^(.*?):([0-9]+):([0-9]+): runtime error: (.*)$", line)
                accepted = m and any(item.get("test", name) == name and m[1].replace("\\", "/").endswith("/" + item["source"]) and int(m[2]) in item["lines"] and re.fullmatch(item["message_pattern"], m[4]) for item in manifest)
                if not accepted:
                    unexpected.append(line)
        missing_diagnostic = expected_diagnostic and error is None and not any("runtime error:" in line or "ERROR: AddressSanitizer" in line for line in output.splitlines())
        if error is not None or unexpected or missing_diagnostic:
            text = "Known sanitizer diagnostic no longer reproduced; see known bugs, it may be a fixed regression. Review the label, scoped manifest and resolved entry." if missing_diagnostic else "\n".join(unexpected) if unexpected else (output if output.strip() else error.get("message", "") + "\n" + "".join(error.itertext()))
            if error is not None and "timeout" in error.get("message", "").lower():
                text = "Test timed out: " + error.get("message")
            kind = "known_changed" if known or expected_diagnostic else "sanitizer" if unexpected or "AddressSanitizer" in text else "test"
            item = finding(kind, name, concise(text), text)
            item["reproduce"] = "ctest --test-dir build -V -R '^" + re.escape(name) + "$'"
            findings.append(item)
            counts["failed"] += 1
        elif known or expected_diagnostic:
            counts["known"] += 1
        else:
            counts["clean"] += 1
    return findings, counts


def source_link(item, lock):
    path = item.get("file", "")
    if not path:
        return ""
    repo, sha, relative = lock.get("harness_repository", ""), lock.get("harness_sha", ""), path
    for source in lock.get("sources", []):
        prefix = source["path"].rstrip("/") + "/"
        if path.startswith(prefix):
            repo, sha, relative = source["repository"], source["sha"], path[len(prefix):]
            break
    label = path + (":" + str(item["line"]) if item.get("line") else "")
    if not re.fullmatch(r"[A-Za-z0-9_.-]+/[A-Za-z0-9_.-]+", repo) or not re.fullmatch(r"[0-9a-fA-F]{40}", sha):
        return html.escape(label)
    from urllib.parse import quote
    return "[" + html.escape(label) + "](https://github.com/" + repo + "/blob/" + sha + "/" + quote(relative) + ("#L" + str(item["line"]) if item.get("line") else "") + ")"


def merge_reports(reports):
    merged = {}
    for report in reports:
        for item in report.get("findings", []):
            key = (item["kind"], item["name"], item.get("file"), item.get("line"), item["message"] if not item.get("file") else "")
            if key not in merged:
                merged[key] = {**item, "jobs": []}
            merged[key]["jobs"].append(report["job"])
    return list(merged.values())


def coverage_totals(path, complete):
    try:
        data = ET.parse(path).getroot().attrib
        values = {key: int(data[key]) for key in
                  ("lines-covered", "lines-valid", "branches-covered", "branches-valid")}
        if any(values[key] < 0 for key in values) or any(
                values[covered] > values[total] for covered, total in
                (("lines-covered", "lines-valid"), ("branches-covered", "branches-valid"))):
            return None
        return dict(values, complete=complete)
    except (OSError, ET.ParseError, KeyError, ValueError):
        return None


def render(reports, lock, outcomes=None):
    findings = merge_reports(reports)
    errors = [f for f in findings if f.get("severity", "error") == "error"]
    warnings = [f for f in findings if f.get("severity") == "warning"]
    changed = [f for f in errors if f["kind"] == "known_changed"]
    unexpected = [f for f in errors if f["kind"] != "known_changed"]
    lines = ["## Why this run failed" if errors else "## CI result", "",
             f"**{len(unexpected)} unexpected failures · {len(changed)} changed known-defect exceptions · {len(warnings)} coverage/review warnings**", ""]
    coverage = next((r["coverage"] for r in reports if r.get("job") == "coverage" and r.get("coverage")), None)
    if coverage:
        if not coverage.get("complete"):
            lines += ["**Partial coverage - build or execution did not complete successfully.**", ""]
        lines += ["| Coverage | Covered / total | Remaining |", "|---|---:|---:|"]
        for label, covered, total in (("Lines", "lines-covered", "lines-valid"),
                                      ("Branches", "branches-covered", "branches-valid")):
            hits, count = coverage[covered], coverage[total]
            rate = f"{100 * hits / count:.2f}%" if count else "N/A"
            lines.append(f"| **{label}: {rate}** | {hits:,} / {count:,} | {count - hits:,} |")
        lines.append("")
    elif outcomes is not None:
        lines += ["**Coverage unavailable** - no measured coverage totals were collected.", ""]
    lines += ["| Job | Tests | Clean passes | Known defects | Failed | Skipped |",
              "|---|---:|---:|---:|---:|---:|"]
    for report in reports:
        counts = report.get("counts", {})
        lines.append("| " + html.escape(report["job"]) + " | " + " | ".join(
            f"{counts[key]:,}" if key in counts else "—"
            for key in ("total", "clean", "known", "failed", "skipped")) + " |")
    lines += ["", "Known defects are expected-failure regressions, separate from clean passes. Compiler rows run the same suite; do not add their totals together.", ""]
    if changed:
        lines.append("Changed known-defect exceptions need review: a regression may now pass while its expected-failure exception remains. Confirm the result, retain correct assertions, and remove only the fixed exception. A different fault is not proof of a fix.")
        lines.append("")
    if not errors:
        lines.append("No unexpected failures in the collected reports. Known defects remain separately labelled.")
    for f in (unexpected + changed + warnings)[:12]:
        name = html.escape(f["name"])
        message = html.escape(f["message"]).replace("|", "&#124;")
        lines.append("- **" + name + "** (" + ", ".join(sorted(set(f["jobs"]))) + "): " + message + (" · " + source_link(f, lock) if f.get("file") else ""))
        if f["kind"] == "known_changed":
            diagnostic_path = lock.get("diagnostics_directory", "tests") + "/KNOWN_BUGS.md"
            link = source_link(dict(file=diagnostic_path, line=None), lock)
            lines.append("  See " + link + "; it may be a fixed regression. If expectations now pass, retain the test, remove its linked exception and delete the resolved entry. A different crash is not proof of a fix.")
        if f.get("reproduce"):
            lines.append("  Reproduce: `" + html.escape(f["reproduce"]) + "`.")
    if len(findings) > 12:
        lines.append(f"{len(findings) - 12} more findings are in the attached JSON reports.")
    lines += ["", "<details><summary>Source revisions</summary>", ""]
    lines += ["", "Harness: `" + lock.get("harness_sha", "unavailable") + "`"]
    for s in lock.get("sources", []):
        lines.append("- " + s["repository"] + " at `" + s["sha"] + "`")
    if lock.get("comparison"):
        lines.append("Changed-code baseline: `" + lock["comparison"]["sha"] + "` (diff from merge base).")
    lines += ["", "</details>", "", "Full logs, per-test results and coverage HTML remain in the run artifacts. Unexpected test failures are suspected regressions until their contract and fixture are checked."]
    return "\n".join(lines) + "\n"


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--job")
    p.add_argument("--aggregate", action="store_true")
    p.add_argument("--reports", default="reports")
    p.add_argument("--test-results", type=Path, default=Path("build/results.xml"))
    args = p.parse_args()
    lock = json.loads(Path("source-lock.json").read_text()) if Path("source-lock.json").exists() else {}
    if args.aggregate:
        reports = [json.loads(p.read_text()) for p in sorted(Path(args.reports).rglob("report-*.json"))]
        needs = json.loads(os.environ.get("NEEDS_JSON", "{}"))
        expected = {"source": ["source"], "test": ["gcc", "clang"], "coverage": ["coverage"]}
        for job, status in needs.items():
            if job == "arm-modules" and status.get("result") == "skipped":
                from check_arm_modules import STM32
                if lock.get("path") not in {"drivers/" + family for family in (*STM32, "lpc176x")}:
                    continue
            present = {r["job"] for r in reports}
            if job != "source" and needs.get("source", {}).get("result") != "success":
                continue
            for missing in set(expected.get(job, [job])) - present:
                reports.append(dict(job=missing, findings=[finding("setup", "Report unavailable", "Job " + status.get("result", "unknown") + "; no diagnostic artifact. Inspect checkout/download or runner logs.")]))
            if status.get("result") in ("failure", "cancelled", "skipped") and not any(f.get("severity", "error") == "error" for r in reports if r["job"] in expected.get(job, [job]) for f in r.get("findings", [])):
                reports.append(dict(job=job, findings=[finding("setup", "Job did not complete successfully", "Job " + status["result"] + "; inspect artifact upload, runner or reporting logs.")]))
        if not reports:
            reports = [dict(job="reporting", findings=[finding("setup", "Reports unavailable", "No job reports were collected; inspect checkout/download steps.")])]
    else:
        path = Path("report-" + args.job + ".json")
        report = json.loads(path.read_text()) if path.exists() else dict(job=args.job, findings=[], stages=[])
        if args.test_results.exists():
            try:
                found, counts = test_findings(args.test_results, lock.get("diagnostics_directory", "tests"))
                report["findings"].extend(found)
                report["counts"] = counts
                if not counts["total"]:
                    report["findings"].append(finding("setup", "No tests executed", "JUnit contains no test cases; check suite registration and CTest selection."))
            except (ET.ParseError, ValueError) as error:
                report["findings"].append(finding("setup", "Invalid test report", str(error)))
        elif args.job != "source" and not report["findings"]:
            report["findings"].append(finding("setup", "Tests did not run", "No JUnit report; inspect the first failed fetch/configure/build step."))
        if not report["findings"]:
            for stage in report.get("stages", []):
                if stage["exit_code"]:
                    detail = Path(stage["log"]).read_text(errors="replace")
                    report["findings"].append(finding("setup", stage["stage"], concise(detail), detail))
                    break
        if args.job == "coverage":
            from changed_coverage import assess
            failed_execution = report.get("counts", {}).get("failed", 0) > 0 or any(
                stage["stage"] in ("build", "test", "classify") and stage["exit_code"]
                for stage in report.get("stages", []))
            stages = {stage["stage"]: stage["exit_code"] for stage in report.get("stages", [])}
            complete = not failed_execution and all(stages.get(stage) == 0 for stage in
                ("fetch", "tooling", "configure", "build", "test", "classify", "coverage"))
            totals = coverage_totals(Path("coverage.xml"), complete)
            if totals is not None:
                report["coverage"] = totals
            if Path("coverage.xml").exists() and failed_execution:
                report["findings"].append(finding("coverage_partial", "Partial coverage",
                    "Build or tests failed; annotated coverage is available for gap investigation, but execution is incomplete. Fix failures before judging changed-code coverage.", severity="warning"))
            else:
                report["findings"].extend(assess(lock, Path("coverage.xml")))
        path.write_text(json.dumps(report, indent=2) + "\n")
        reports = [report]
    text = render(reports, lock, needs if args.aggregate else None)
    if os.environ.get("GITHUB_STEP_SUMMARY"):
        with open(os.environ["GITHUB_STEP_SUMMARY"], "a", encoding="utf-8") as f:
            f.write(text)
    else:
        print(text.encode("ascii", "backslashreplace").decode("ascii"))
    if args.aggregate and os.environ.get("GITHUB_ACTIONS") == "true":
        for item in merge_reports(reports)[:12]:
            message = (item["name"] + ": " + item["message"] + (" · " + source_link(item, lock) if item.get("file") else "")).replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")
            title = (item["kind"] + ": " + item["name"]).replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A").replace(":", "%3A").replace(",", "%2C")
            properties = "title=" + title
            if os.environ.get("GITHUB_REPOSITORY") == lock.get("harness_repository") and item.get("line") and item.get("file", "").startswith(("tests/", "scripts/")):
                properties += ",file=" + item["file"].replace("%", "%25").replace(",", "%2C") + ",line=" + str(item["line"])
            print("::" + ("warning" if item.get("severity") == "warning" else "error") + " " + properties + "::" + message)
    if any(f.get("severity", "error") == "error" for r in reports for f in r.get("findings", [])):
        raise SystemExit(1)

if __name__ == "__main__":
    main()
