"""Recognize only explicitly inventoried fatal ASan regressions."""
import json
from pathlib import Path
import re
import subprocess
import sys


def matches_known_crash(name, output, manifest):
    errors = [line for line in output.splitlines() if "ERROR: AddressSanitizer:" in line]
    summaries = [line for line in output.splitlines() if "SUMMARY: AddressSanitizer:" in line]
    if (len(errors) != 1 or len(summaries) != 1
            or len(re.findall(r"(?:ERROR|WARNING): \w*Sanitizer:", output)) != 1):
        return False
    for item in manifest:
        if item.get("kind") != "fatal_asan" or item.get("test") != name:
            continue
        source = re.escape(item["source"]).replace("/", r"[/\\]")
        source_line = source + r":(?:" + "|".join(map(str, item["lines"])) + r")"
        location = source_line + r":\d+\b"
        asan_location = source_line + r"(?::\d+)?\b"
        runtime = [line for line in output.splitlines() if "runtime error:" in line]
        ubsan = item.get("preceding_ubsan_pattern")
        if runtime and not (ubsan and len(runtime) == 1 and re.fullmatch(
                r".*[/\\]" + location + r": runtime error: " + ubsan, runtime[0])):
            continue
        if ubsan and not runtime:
            continue
        ubsan_summaries = [line for line in output.splitlines() if "SUMMARY: UndefinedBehaviorSanitizer:" in line]
        if ubsan_summaries and not (ubsan and len(ubsan_summaries) == 1 and re.fullmatch(
                r"SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior .*[/\\]" + location + r"\s*", ubsan_summaries[0])):
            continue
        # GCC reports a NULL indirect call at PC zero and omits the tail-called
        # CORE frame. Require the exact recorded harness caller chain instead.
        frames = item.get("zero_pc_frames", [])
        if (frames and re.search(r"ERROR: AddressSanitizer: SEGV on unknown address 0x0+ \(pc 0x0+\b", errors[0])
                and summaries[0].strip() == "SUMMARY: AddressSanitizer: SEGV (<unknown module>)"
                and re.search(r"^\s*#0 0x0+  \(<unknown module>\)", output, re.MULTILINE)):
            if all(re.search(r"^\s*#" + str(index) + r" 0x[0-9a-f]+ in " + re.escape(frame["function"])
                             + r" .*[/\\]" + re.escape(frame["source"]).replace("/", r"[/\\]")
                             + ":" + str(frame["line"]) + r"(?::[0-9]+)?(?:\s|$)", output, re.MULTILINE)
                   for index, frame in enumerate(frames, 1)):
                return True
        # Some Windows LLVM builds omit ASan line numbers even with a precise UBSan location.
        if item.get("asan_line_optional") and ubsan and runtime:
            asan_location = source + r"(?::(?:" + "|".join(map(str, item["lines"])) + r")(?::\d+)?)?(?!:\d)\b"
        if (re.search(r"ERROR: AddressSanitizer: " + item["message_pattern"] + r"\b", errors[0])
                and re.search(r"SUMMARY: AddressSanitizer: " + item["message_pattern"] + r" .*" + asan_location + r" in " + re.escape(item["function"]) + r"\b", summaries[0])
                and re.search(r"#0 .* in " + re.escape(item["function"]) + r" .*" + asan_location, output)):
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
        if not any("Sanitizer:" in line or "runtime error:" in line for line in result.stdout.splitlines()):
            for item in manifest:
                if (item.get("test") == name and item.get("unsanitized_marker")
                        and result.stdout.strip() == item["unsanitized_marker"]
                        and result.returncode in item.get("unsanitized_exit_codes", [])):
                    print(result.stdout)
                    print("Documented process fault reproduced; assertions after the fault did not run.")
                    return 1
        if result.returncode and matches_known_crash(name, result.stdout, manifest):
            # CTest truncates passing output to 1KiB. Keep the exact matching
            # evidence together; preserve the complete process output separately.
            for line in result.stdout.splitlines():
                if "runtime error:" in line or "UndefinedBehaviorSanitizer:" in line or "ERROR: AddressSanitizer:" in line or "SUMMARY: AddressSanitizer:" in line or re.search(r"#0 ", line) or ("Hint: pc points to the zero page." in result.stdout and re.search(r"#[12] ", line)):
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
