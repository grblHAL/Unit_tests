"""Recognize only the documented unavailable RS485-direction startup crash."""
import re
import subprocess
import sys


def matches_known_crash(output):
    # GCC's null indirect call has no callee frame. Require the captured zero-PC
    # diagnostic and the exact initializer callsite, as well as this regression.
    gcc_null_call = (
        re.search(r"pc 0x0+\b", output)
        and "Hint: pc points to the zero page." in output
        and re.search(r"#0 0x0+\s+\(<unknown module>\)", output)
        and re.search(r"#1 [^\n]*in initialize_rtu_transport[^\n]*tests[/\\]support[/\\]rtu_host\.h:63\b", output)
    )
    return bool(
        re.search(r"ERROR: AddressSanitizer: (?:SEGV|access-violation) on unknown address 0x(?:0+|f+8)\b", output)
        and (gcc_null_call or re.search(r"#(?:0|1) [^\n]*modbus_rtu_init[^\n]*core[/\\]modbus_rtu\.c:601\b", output))
        and re.search(r"in main[^\n]*aux_direction_without_outputs_disables_transport_safely\.c:5\b", output)
    )


def main():
    if sys.argv[1] != "1":
        print("This known startup memory fault requires ENABLE_SANITIZERS=ON.")
        return 77
    result = subprocess.run([sys.argv[2]], stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, text=True)
    print(result.stdout)
    print(f"Regression executable exit code: {result.returncode}")
    if result.returncode != 0 and matches_known_crash(result.stdout):
        print("Confirmed known unavailable RS485-direction startup crash.")
        return 1
    if result.returncode == 0:
        print("Regression passed: see KNOWN_BUGS.md and remove the fixed exception.")
    else:
        print("Unexpected failure: inspect the diagnostic above; it does not match the known crash.")
    # WILL_FAIL deliberately makes a fixed regression or a different fault red.
    return 0


if __name__ == "__main__":
    sys.exit(main())
