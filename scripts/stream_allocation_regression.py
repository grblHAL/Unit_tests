"""Recognize only the null connection write after injected stream allocation failure."""
import re
import subprocess
import sys


def matches_known_crash(output):
    return bool(
        "Injected auxiliary stream allocation failure" in output
        and re.search(r"core[/\\]stream\.c:310:\d+: runtime error: member access within null pointer of type '(?:struct )?stream_connection(?:_t)?'", output)
        and re.search(r"ERROR: AddressSanitizer: (?:access-violation|SEGV) on unknown address 0x0*8\b", output)
        and "WRITE memory access" in output
        and re.search(r"in add_connection[^\n]*core[/\\]stream\.c", output)
        and re.search(r"in stream_connect[^\n]*core[/\\]stream\.c:489\b", output)
        and re.search(r"in main[^\n]*auxiliary_connection_allocation_failure_preserves_primary_stream\.c:7\b", output)
        and re.search(r"SUMMARY: AddressSanitizer: (?:access-violation|SEGV)[^\n]*add_connection", output)
    )


def main():
    if sys.argv[1] != "1":
        print("This known null stream connection fault requires ENABLE_SANITIZERS=ON.")
        return 77
    result = subprocess.run([sys.argv[2]], stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, text=True)
    print(result.stdout)
    print(f"Regression executable exit code: {result.returncode}")
    if result.returncode != 0 and matches_known_crash(result.stdout):
        print("Confirmed known null connection write after stream allocation failure.")
        return 1
    if result.returncode == 0:
        print("Regression passed: see KNOWN_BUGS.md and remove the fixed exception.")
    else:
        print("Unexpected failure: diagnostic does not match the known stream allocation fault.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
