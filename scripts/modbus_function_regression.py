"""Match only the documented null descriptor dereference in the Modbus macro."""
import re
import subprocess
import sys

if sys.argv[1] != "1":
    print("This known null-pointer defect requires ENABLE_SANITIZERS=ON.")
    sys.exit(77)
result = subprocess.run([sys.argv[2]], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
print(result.stdout)
print(f"Regression executable exit code: {result.returncode}")
expected = (
    re.search(r"core[/\\]ngc_params\.c:1225:[0-9]+: runtime error: (?:member access within null pointer|load of null pointer)", result.stdout)
    and re.search(r"ERROR: AddressSanitizer: (?:SEGV|access-violation) on unknown address 0x0+\b", result.stdout)
    and "The signal is caused by a READ memory access." in result.stdout
    and re.search(r"macro_modbus_msg[^\n]*core[/\\]ngc_params\.c", result.stdout)
)
# A fix or any unrelated failure must fail WILL_FAIL and force review.
if result.returncode != 0 and expected:
    print("Confirmed known null Modbus function descriptor dereference at core/ngc_params.c:1225.")
    sys.exit(1)
print("Expected sanitizer diagnostic was not reproduced; review this regression.")
sys.exit(0)
