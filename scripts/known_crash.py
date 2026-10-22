"""Recognize only explicitly inventoried fatal ASan regressions."""
import json
from pathlib import Path
import re
import subprocess
import sys


def matches_known_crash(name, output, manifest):
    errors = [line for line in output.splitlines() if "ERROR: AddressSanitizer:" in line]
    summaries = [line for line in output.splitlines() if "SUMMARY: AddressSanitizer:" in line]
    if (len(errors) != 1 or len(summaries) != 1 or "runtime error:" in output
            or len(re.findall(r"(?:ERROR|WARNING): \w*Sanitizer:", output)) != 1):
        return False
    for item in manifest:
        if item.get("kind") != "fatal_asan" or item.get("test") != name:
            continue
        source = re.escape(item["source"]).replace("/", r"[/\\]")
        location = source + r":(?:" + "|".join(map(str, item["lines"])) + r"):\d+\b"
        if (re.search(r"ERROR: AddressSanitizer: " + item["message_pattern"] + r"\b", errors[0])
                and re.search(r"SUMMARY: AddressSanitizer: " + item["message_pattern"] + r" .*" + location + r" in " + re.escape(item["function"]) + r"\b", summaries[0])
                and re.search(r"#0 .* in " + re.escape(item["function"]) + r" .*" + location, output)):
            return True
    return False


def main():
    # WILL_FAIL accepts only our deliberate 1. Fixes, unrelated faults and runner
    # errors return 0 so the obsolete/incorrect exception makes CTest red.
    try:
        name, inventory, executable = sys.argv[1:]
        manifest = json.loads(Path(inventory).read_text(encoding="utf-8"))
        result = subprocess.run([executable], stdout=subprocess.PIPE,
                                stderr=subprocess.STDOUT, text=True, errors="replace", timeout=10)
        log = Path("known-crash-" + name + ".log")
        log.write_text(result.stdout, encoding="utf-8")
        if result.returncode and matches_known_crash(name, result.stdout, manifest):
            # CTest truncates passing output to 1KiB. Keep the exact matching
            # evidence together; preserve the complete process output separately.
            for line in result.stdout.splitlines():
                if "ERROR: AddressSanitizer:" in line or "SUMMARY: AddressSanitizer:" in line or re.search(r"#0 ", line):
                    print(line)
            print("Full process output:", log.resolve())
            print("Documented fatal regression reproduced; assertions after the crash did not run.")
            return 1
        print(result.stdout)
        print("Regression executable exit code:", result.returncode)
        print("Expected fatal diagnostic absent or changed; review exception and retain regression.")
    except Exception as error:
        print("Diagnostic runner failed:", error)
    return 0


if __name__ == "__main__":
    sys.exit(main())
