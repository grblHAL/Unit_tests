"""Match only the documented BUILD_INFO overread during settings recovery."""
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
    "ERROR: AddressSanitizer: global-buffer-overflow" in result.stdout
    and "READ of size 70" in result.stdout
    and re.search(r"settings_write_build_info[^\n]*core[/\\]settings\.c:2825\b", result.stdout)
    and re.search(r"settings_restore[^\n]*core[/\\]settings\.c:3041\b", result.stdout)
)
# WILL_FAIL accepts only the confirmed defect. Success or a different failure
# requires review instead of silently passing the known regression.
if result.returncode != 0 and expected:
    print("Confirmed known BUILD_INFO record overread during settings recovery.")
    sys.exit(1)
print("Expected sanitizer diagnostic was not reproduced; review this regression.")
sys.exit(0)
