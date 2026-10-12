"""Accept only the confirmed named-subroutine callback use-after-free."""
import re
import subprocess
import sys

if sys.argv[1] != "1":
    print("This known memory defect requires ENABLE_SANITIZERS=ON.")
    sys.exit(77)
result = subprocess.run([sys.argv[2]], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
print(result.stdout)
print(f"Regression executable exit code: {result.returncode}")
expected = (
    "ERROR: AddressSanitizer: heap-use-after-free" in result.stdout
    and "READ of size 8" in result.stdout
    and re.search(r"SUMMARY: AddressSanitizer: heap-use-after-free[^\n]*core[/\\]ngc_flowctrl\.c:316\b", result.stdout)
    and re.search(r"clear_subs[^\n]*core[/\\]ngc_flowctrl\.c:259\b", result.stdout)
)
# WILL_FAIL accepts only this exact memory defect. A fix or a different failure
# returns zero and fails the regression, requiring removal or review.
if result.returncode != 0 and expected:
    print("Confirmed known named-subroutine callback lifetime defect at core/ngc_flowctrl.c:316.")
    sys.exit(1)
print("Expected sanitizer diagnostic was not reproduced; review this regression.")
sys.exit(0)
