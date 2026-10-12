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
args = parser.parse_args()
lines = []
sanitizer_failures = []
known_diagnostics = []
manifest = json.loads((Path(__file__).resolve().parents[1] / "tests/known_sanitizer_diagnostics.json").read_text(encoding="utf-8"))
if not args.path.exists():
    lines = ["## Report unavailable", "Build or test execution did not produce the expected report."]
else:
    root = ET.parse(args.path).getroot()
    if args.kind == "tests":
        cases = list(root.iter("testcase"))
        failed = sum(c.find("failure") is not None or c.find("error") is not None for c in cases)
        known = sum(any(p.get("name") == "cmake_labels" and "known_bug" in p.get("value", "").split(";") for p in c.findall("./properties/property")) and c.find("failure") is None and c.find("skipped") is None for c in cases)
        for case in cases:
            labelled = any(p.get("name") == "cmake_labels" and "known_bug" in p.get("value", "").split(";") for p in case.findall("./properties/property"))
            if labelled or any(case.find(tag) is not None for tag in ("failure", "error", "skipped")):
                continue
            diagnostics = []
            for line in case.findtext("system-out", "").splitlines():
                if "runtime error:" not in line and "ERROR: AddressSanitizer" not in line:
                    continue
                match = re.match(r"^(.*?):([0-9]+):([0-9]+): runtime error: (.*)$", line)
                recognized = match and any(
                    match[1].replace("\\", "/").endswith("/" + item["source"])
                    and int(match[2]) in item["lines"]
                    and re.fullmatch(item["message_pattern"], match[4])
                    for item in manifest)
                diagnostics.append((line, bool(recognized)))
            if diagnostics:
                if all(known for _, known in diagnostics):
                    known_diagnostics.append(case.get("name", "unknown"))
                else:
                    sanitizer_failures.append(case.get("name", "unknown"))
                case.set("sanitizer_status", "known" if all(known for _, known in diagnostics) else "failed")
                case.set("sanitizer_output", "\n".join(line for line, _ in diagnostics))
        failed += len(sanitizer_failures)
        skipped = sum(c.find("skipped") is not None for c in cases)
        lines = ["## Core test results", "Tests labelled `known_bug` are expected failures confirming documented upstream defects; see tests/KNOWN_BUGS.md.", f"**{len(cases) - failed - skipped - known - len(known_diagnostics)} clean passes · {len(known_diagnostics)} passed with known sanitizer diagnostics · {known} known regressions reproduced · {failed} failed · {skipped} skipped**", "", "| Test | Result | Seconds |", "|---|---|---:|"]
        for case in cases:
            status = "❌ Failed" if case.find("failure") is not None or case.find("error") is not None else "⏭ Skipped" if case.find("skipped") is not None else "✅ Passed"
            if any(p.get("name") == "cmake_labels" and "known_bug" in p.get("value", "").split(";") for p in case.findall("./properties/property")) and case.find("failure") is None and case.find("skipped") is None:
                status = "⚠️ Known defect reproduced"
            if case.get("sanitizer_status"):
                status = "⚠️ Assertions passed; known sanitizer diagnostic" if case.get("sanitizer_status") == "known" else "❌ Unexpected sanitizer diagnostic"
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
                        description = "\n".join(part for part in (case.get("name", "unknown"), detail.get("message", ""), "".join(detail.itertext()), output) if part)
                        # Escape workflow commands so test output remains data.
                        message = description[-6000:].replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")
                        title = ("Test " + case.get("name", "unknown")).replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A").replace(":", "%3A").replace(",", "%2C")
                        print(f"::error title={title}::{message}")
        for case in cases:
            if case.get("sanitizer_output"):
                lines.extend(["", "<details><summary>Sanitizer output: " + html.escape(case.get("name", "unknown")) + "</summary><pre>" + html.escape(case.get("sanitizer_output")) + "</pre></details>", ""])
        if known_diagnostics and os.environ.get("GITHUB_ACTIONS") == "true":
            print(f"::warning title=Known sanitizer diagnostics::{len(known_diagnostics)} tests passed assertions but reproduced diagnostics documented in tests/KNOWN_BUGS.md; review tests/known_sanitizer_diagnostics.json when updating core.")
    else:
        measured = {entry.get("filename", "").replace("\\", "/"): entry for entry in root.iter("class")}
        inventory = sorted(path.as_posix() for path in Path("core").rglob("*.c"))
        lines = ["## Core coverage", f"**{len(measured)} of {len(inventory)} core source files instrumented**", "The remaining files are visible below; percentages apply to this build configuration.", "", "| Module | Line coverage | Lines | Branches |", "|---|---|---:|---:|"]
        for filename in inventory:
            if entry := measured.get(filename):
                rate = float(entry.get("line-rate", "0"))
                filled = round(rate * 10)
                bar = "🟩" * filled + "⬜" * (10 - filled)
                lines.append(f"| {filename} | {bar} | {rate * 100:.1f}% | {float(entry.get('branch-rate', '0')) * 100:.1f}% |")
            else:
                lines.append(f"| {filename} | ⬜ Not instrumented | — | — |")
        lines.extend(["", "Download the coverage artifact for annotated source and branch details. Known defects have separate labelled regressions; coverage does not imply correctness."])
report = "\n".join(lines) + "\n"
if target := os.environ.get("GITHUB_STEP_SUMMARY"):
    with open(target, "a", encoding="utf-8") as stream:
        stream.write(report)
else:
    print(report.encode("ascii", "backslashreplace").decode("ascii"))

if sanitizer_failures:
    raise SystemExit(1)
