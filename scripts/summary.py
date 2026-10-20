"""Render CTest JUnit results and Cobertura coverage into GitHub job summaries."""
import argparse
import html
import json
import re
import os
from pathlib import Path
import xml.etree.ElementTree as ET

parser = argparse.ArgumentParser()
parser.add_argument("kind", choices=["tests", "coverage"])
parser.add_argument("path", type=Path)
parser.add_argument("--diagnostics-directory", type=Path, default=Path(__file__).resolve().parents[1] / "tests")
parser.add_argument("--source-directory", type=Path, default=Path("core"))
parser.add_argument("--suite-name", default="Core")
args = parser.parse_args()
def harness_link(path):
    path = Path(path)
    if path.is_absolute():
        try:
            path = path.relative_to(Path(__file__).resolve().parents[1])
        except ValueError:
            return path.as_posix()
    if Path("source-lock.json").exists():
        lock = json.loads(Path("source-lock.json").read_text(encoding="utf-8"))
        repository, sha = lock.get("harness_repository", ""), lock.get("harness_sha", "")
        if re.fullmatch(r"[A-Za-z0-9_.-]+/[A-Za-z0-9_.-]+", repository) and re.fullmatch(r"[0-9a-fA-F]{40}", sha):
            return "https://github.com/" + repository + "/blob/" + sha + "/" + path.as_posix()
    return path.as_posix()

known_link = "[known bugs](" + harness_link(args.diagnostics_directory / "KNOWN_BUGS.md") + ")"
failed = 0
lines = []
sanitizer_failures = []
known_diagnostics = []
manifest = json.loads((args.diagnostics_directory / "known_sanitizer_diagnostics.json").read_text(encoding="utf-8")) if args.kind == "tests" else []
if not args.path.exists():
    lines = ["## Report unavailable", "Build or test execution did not produce the expected report.", "Inspect the first failing Configure/Build/Test step and its compiler output. Check the source-lock artifact for the exact source and harness revisions, then reproduce that configuration locally. Resolve source/API or fixture compatibility errors; no test result or coverage conclusion is available until the build and tests run."]
else:
    root = ET.parse(args.path).getroot()
    if args.kind == "tests":
        cases = list(root.iter("testcase"))
        failed = sum(c.find("failure") is not None or c.find("error") is not None for c in cases)
        for case in cases:
            if any(case.find(tag) is not None for tag in ("failure", "error", "skipped")):
                continue
            expected_diagnostic = any(p.get("name") == "cmake_labels" and "known_sanitizer_bug" in p.get("value", "").split(";") for p in case.findall("./properties/property"))
            diagnostics = []
            output = "\n".join(case.findtext(tag, "") for tag in ("system-out", "system-err"))
            for line in output.splitlines():
                if "runtime error:" not in line and "ERROR: AddressSanitizer" not in line:
                    continue
                match = re.match(r"^(.*?):([0-9]+):([0-9]+): runtime error: (.*)$", line)
                recognized = match and any(
                    item.get("test", case.get("name")) == case.get("name")
                    and match[1].replace("\\", "/").endswith("/" + item["source"])
                    and int(match[2]) in item["lines"]
                    and re.fullmatch(item["message_pattern"], match[4])
                    for item in manifest)
                diagnostics.append((line, bool(recognized)))
            if expected_diagnostic and not diagnostics:
                sanitizer_failures.append(case.get("name", "unknown"))
                ET.SubElement(case, "failure", message="Known sanitizer diagnostic no longer reproduced; see known bugs, it may be a fixed regression.")
                case.set("sanitizer_status", "missing")
                case.set("sanitizer_output", "Expected diagnostic absent. Retain the correct test; review and remove its known_sanitizer_bug label, scoped manifest entry and resolved KNOWN_BUGS.md entry if fixed.")
            if diagnostics:
                if all(known for _, known in diagnostics):
                    known_diagnostics.append(case.get("name", "unknown"))
                else:
                    sanitizer_failures.append(case.get("name", "unknown"))
                case.set("sanitizer_status", "known" if all(known for _, known in diagnostics) else "failed")
                case.set("sanitizer_output", "\n".join(line for line, _ in diagnostics))
        failed += len(sanitizer_failures)
        known = sum(any(p.get("name") == "cmake_labels" and "known_bug" in p.get("value", "").split(";") for p in c.findall("./properties/property"))
                    and not any(c.find(tag) is not None for tag in ("failure", "error", "skipped"))
                    and c.get("sanitizer_status") is None for c in cases)
        skipped = sum(c.find("skipped") is not None for c in cases)
        lines = [f"## {args.suite_name} test results", f"Tests labelled `known_bug` are expected failures confirming documented defects; see {args.diagnostics_directory.as_posix()}/KNOWN_BUGS.md.", f"**{len(cases) - failed - skipped - known - len(known_diagnostics)} clean passes · {len(known_diagnostics)} passed with known sanitizer diagnostics · {known} known regressions reproduced · {failed} failed · {skipped} skipped**", "", "| Test | Result | Seconds |", "|---|---|---:|"]
        affected = [case for case in cases if case.find("failure") is not None or case.find("error") is not None or case.get("sanitizer_status") in ("failed", "missing")]
        if affected:
            guidance = ["", "### Failure guidance", ""]
            for case in affected:
                name = html.escape(case.get("name", "unknown")).replace("|", "&#124;")
                labelled = any(p.get("name") == "cmake_labels" and any(label in p.get("value", "").split(";") for label in ("known_bug", "known_sanitizer_bug")) for p in case.findall("./properties/property"))
                if labelled:
                    advice = "See " + known_link + "; it may be a fixed regression. Inspect the actual assertion/diagnostic before concluding it is fixed. If the correct expectations now pass, retain the test, remove only its linked WILL_FAIL/sanitizer/wrapper exception, delete the resolved known-bug entry, and rerun the suite plus summary. An unrelated crash or different failure is not proof of a fix."
                else:
                    advice = "Inspect the failing assertion and LastTest.log; reproduce with `ctest --test-dir build -V -R` and this test's name. Compare the selected source change with the intended contract and fixture startup/configuration. Fix a source regression, or update the test/fixture only for a confirmed intended API/behavior change. Add boundary/error coverage for new behavior; do not weaken assertions or broadly suppress sanitizer failures."
                case.set("failure_guidance", advice)
                guidance.append("- **" + name + ":** " + advice)
            lines[3:3] = guidance + [""]
        for case in cases:
            status = "❌ Failed" if case.find("failure") is not None or case.find("error") is not None else "⏭ Skipped" if case.find("skipped") is not None else "✅ Passed"
            if any(p.get("name") == "cmake_labels" and "known_bug" in p.get("value", "").split(";") for p in case.findall("./properties/property")) and case.find("failure") is None and case.find("skipped") is None:
                status = "⚠️ Known defect reproduced"
            if any(p.get("name") == "cmake_labels" and "known_bug" in p.get("value", "").split(";") for p in case.findall("./properties/property")) and (case.find("failure") is not None or case.find("error") is not None):
                status = "❌ Known regression changed; see guidance"
            if case.get("sanitizer_status"):
                status = "⚠️ Assertions passed; known sanitizer diagnostic" if case.get("sanitizer_status") == "known" else "❌ Known sanitizer diagnostic absent; review exception" if case.get("sanitizer_status") == "missing" else "❌ Unexpected sanitizer diagnostic"
                if case.get("sanitizer_status") == "failed" and os.environ.get("GITHUB_ACTIONS") == "true":
                    message = (case.get("name", "unknown") + "\n" + case.get("sanitizer_output"))[-6000:].replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")
                    print(f"::error title=Unexpected sanitizer diagnostic::{message}")
            name = html.escape(case.get("name", "unknown")).replace("|", "&#124;")
            lines.append(f"| {name} | {status} | {case.get('time', '0')} |")
            for tag in ("failure", "error"):
                detail = case.find(tag)
                if detail is not None:
                    lines.extend(["", f"<details><summary>{name} failure</summary><pre>{html.escape(''.join(detail.itertext()))}</pre></details>", ""])
                    if os.environ.get("GITHUB_ACTIONS") == "true":
                        output = case.findtext("system-out", "")
                        description = "\n".join(part for part in (case.get("name", "unknown"), case.get("failure_guidance", ""), detail.get("message", ""), "".join(detail.itertext()), output) if part)
                        # Escape workflow commands so test output remains data.
                        message = description[-6000:].replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")
                        title = ("Test " + case.get("name", "unknown")).replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A").replace(":", "%3A").replace(",", "%2C")
                        print(f"::error title={title}::{message}")
        for case in cases:
            if case.get("sanitizer_output"):
                lines.extend(["", "<details><summary>Sanitizer output: " + html.escape(case.get("name", "unknown")) + "</summary><pre>" + html.escape(case.get("sanitizer_output")) + "</pre></details>", ""])
        if known_diagnostics and os.environ.get("GITHUB_ACTIONS") == "true":
            print(f"::warning title=Known sanitizer diagnostics::{len(known_diagnostics)} tests passed assertions but reproduced diagnostics documented in {args.diagnostics_directory.as_posix()}/KNOWN_BUGS.md; review its known_sanitizer_diagnostics.json when updating sources.")
    else:
        measured = {entry.get("filename", "").replace("\\", "/"): entry for entry in root.iter("class")}
        inventory = sorted(path.as_posix() for path in args.source_directory.rglob("*.c"))
        lines = [f"## {args.suite_name} coverage", f"**{len(measured)} of {len(inventory)} source files instrumented**", "The remaining files are visible below; percentages apply to this build configuration.", "", "| Module | Line coverage | Lines | Branches |", "|---|---|---:|---:|"]
        if os.environ.get("COVERAGE_COMPLETE") == "false":
            lines[1:1] = ["**Partial coverage: tests failed.** These measurements describe incomplete execution; they do not establish a passing baseline or prove that uncovered code has no tests.", ""]
        missing = [name for name in inventory if name not in measured]
        uncovered = [name for name in inventory if name in measured and float(measured[name].get("line-rate", "0")) < 1]
        if missing or uncovered:
            lines[3:3] = ["", "### Coverage guidance", "", f"{len(missing)} files are absent from this coverage configuration; {len(uncovered)} measured files have uncovered executable lines.", "For new or changed code, inspect annotated HTML coverage and add meaningful tests for uncovered behavior and error paths. If a source file is absent, check its CMake inclusion, feature flags and coverage filter before concluding it lacks tests. Register new modules/plugin suites and their representative host fixtures/configurations.", "Coverage gaps alone do not establish that code is newly added or has no tests; that requires a source diff against a specified baseline. These gaps are reported for review, not automatically waived or treated as proof of correctness.", ""]
        for filename in inventory:
            if entry := measured.get(filename):
                rate = float(entry.get("line-rate", "0"))
                filled = round(rate * 10)
                bar = "🟩" * filled + "⬜" * (10 - filled)
                lines.append(f"| {filename} | {bar} | {rate * 100:.1f}% | {float(entry.get('branch-rate', '0')) * 100:.1f}% |")
            else:
                lines.append(f"| {filename} | ⬜ Not instrumented | — | — |")
        lines.extend(["", "Download the coverage artifact for annotated source and branch details. Known defects have separate labelled regressions; coverage does not imply correctness."])
# Detailed inventories remain expandable; CI diagnosis contains short findings.
if args.path.exists():
    lines = ["<details><summary>Detailed " + args.kind + " results</summary>", ""] + lines + ["", "</details>"]
report = "\n".join(lines) + "\n"
if target := os.environ.get("GITHUB_STEP_SUMMARY"):
    with open(target, "a", encoding="utf-8") as stream:
        stream.write(report)
else:
    print(report.encode("ascii", "backslashreplace").decode("ascii"))

if sanitizer_failures or failed or not args.path.exists():
    raise SystemExit(1)
