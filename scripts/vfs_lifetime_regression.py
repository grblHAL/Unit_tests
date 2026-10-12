"""Match only the documented VFS sanitizer defect; unrelated errors fail CTest."""
import re
import subprocess
import sys

if sys.argv[1] != "1":
    print("This known memory defect requires ENABLE_SANITIZERS=ON.")
    sys.exit(77)
result = subprocess.run([sys.argv[2]], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
print(result.stdout)
print(f"Regression executable exit code: {result.returncode}")
# CTest WILL_FAIL expects 1 only for this confirmed diagnostic. A fix or any
# different failure returns 0, making CTest fail and requiring review.
expected = re.search(r"SUMMARY: AddressSanitizer: heap-use-after-free[^\n]*core[/\\]vfs\.c:(?:367|368)\b", result.stdout)
if result.returncode != 0 and expected:
    print("Confirmed known VFS close lifetime defect at core/vfs.c:367-368.")
    sys.exit(1)
print("Expected sanitizer diagnostic was not reproduced; review this regression.")
sys.exit(0)
