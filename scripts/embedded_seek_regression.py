"""Accept only the confirmed embedded-handle overread; fixes require cleanup."""
import re
import subprocess
import sys

if sys.argv[1] != "1":
    print("This known memory defect requires ENABLE_SANITIZERS=ON.")
    sys.exit(77)
result = subprocess.run([sys.argv[2]], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
print(result.stdout)
expected = re.search(r"SUMMARY: AddressSanitizer: global-buffer-overflow[^\n]*core[/\\]fs_embedded\.c:122\b", result.stdout)
if result.returncode and expected and "READ of size 8" in result.stdout:
    print("Confirmed embedded seek handle overread; see KNOWN_BUGS.md#embedded-filesystem-seek.")
    sys.exit(1)
print("Expected embedded seek diagnostic absent; remove the exception if fixed, otherwise inspect this failure.")
sys.exit(0)
