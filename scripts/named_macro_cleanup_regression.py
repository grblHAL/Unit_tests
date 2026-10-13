"""Match only the remaining subroutine lifetime defect on embedded macro return."""
import re
import subprocess
import sys

if sys.argv[1] != "1":
    print("These known memory defects require ENABLE_SANITIZERS=ON.")
    sys.exit(77)
result = subprocess.run([sys.argv[2]], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
print(result.stdout)
print(f"Regression executable exit code: {result.returncode}")
sub_defect = (
    "READ of size 8" in result.stdout
    and re.search(r"SUMMARY: AddressSanitizer: heap-use-after-free[^\n]*core[/\\]ngc_flowctrl\.c:316\b", result.stdout)
    and re.search(r"clear_subs[^\n]*core[/\\]ngc_flowctrl\.c:259\b", result.stdout)
)
if result.returncode != 0 and sub_defect:
    print("Confirmed known embedded named-macro cleanup lifetime defect.")
    sys.exit(1)
print("Expected sanitizer diagnostic was not reproduced; review this regression.")
sys.exit(0)
