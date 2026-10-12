"""Match only the two confirmed lifetime defects on embedded named-macro return."""
import re
import subprocess
import sys

if sys.argv[1] != "1":
    print("These known memory defects require ENABLE_SANITIZERS=ON.")
    sys.exit(77)
result = subprocess.run([sys.argv[2]], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
print(result.stdout)
print(f"Regression executable exit code: {result.returncode}")
vfs_defect = (
    re.search(r"SUMMARY: AddressSanitizer: heap-use-after-free[^\n]*core[/\\]vfs\.c:(?:367|368)\b", result.stdout)
    and re.search(r"fs_close[^\n]*core[/\\]fs_embedded\.c:86\b", result.stdout)
    and re.search(r"stream_redirect_close[^\n]*core[/\\]stream_file\.c:203\b", result.stdout)
)
sub_defect = (
    "READ of size 8" in result.stdout
    and re.search(r"SUMMARY: AddressSanitizer: heap-use-after-free[^\n]*core[/\\]ngc_flowctrl\.c:316\b", result.stdout)
    and re.search(r"clear_subs[^\n]*core[/\\]ngc_flowctrl\.c:259\b", result.stdout)
)
# Compilers expose different first faults on the same cleanup path.
# Only these documented faults pass WILL_FAIL; success or any different fault
# returns zero and requires review.
if result.returncode != 0 and (vfs_defect or sub_defect):
    print("Confirmed known embedded named-macro cleanup lifetime defect.")
    sys.exit(1)
print("Expected sanitizer diagnostic was not reproduced; review this regression.")
sys.exit(0)
