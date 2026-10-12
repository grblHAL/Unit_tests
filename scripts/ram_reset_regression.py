"""Match only the documented stale RAM file list after reset."""
import re
import subprocess
import sys

if sys.argv[1] != "1":
    print("This known memory defect requires ENABLE_SANITIZERS=ON.")
    sys.exit(77)
result = subprocess.run([sys.argv[2]], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
print(result.stdout)
print(f"Regression executable exit code: {result.returncode}")
# WILL_FAIL accepts only this reset/lookup use-after-free, never another error.
lookup = re.search(r"find_file[^\n]*core[/\\]fs_ram\.c:85\b", result.stdout)
reset = re.search(r"fs_reset[^\n]*core[/\\]fs_ram\.c:337\b", result.stdout)
expected = "ERROR: AddressSanitizer: heap-use-after-free" in result.stdout
if result.returncode != 0 and expected and lookup and reset:
    print("Confirmed stale RAM file list after reset at core/fs_ram.c:85/337.")
    sys.exit(1)
print("Expected reset diagnostic was not reproduced; review this regression.")
sys.exit(0)
