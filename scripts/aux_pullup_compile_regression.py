"""Compile the pullup feature and match only its documented stale-symbol error."""
import re
import subprocess
import sys

result = subprocess.run([sys.argv[1], "-std=c11", "-fsyntax-only", "-DAUX_SETTINGS_PULLUP=1", "-I" + sys.argv[2], sys.argv[3]], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
print(result.stdout)
print(f"Compiler exit code: {result.returncode}")
errors = [line for line in result.stdout.splitlines() if ": error:" in line]
primary = re.compile(r"ioports\.c:1446:[0-9]+: error:.*")
secondary = re.compile(r"ioports\.c:1646:[0-9]+: error:.*")
expected = any(primary.search(line) and "digital" in line and "undeclared" in line for line in errors)
expected = expected and all(
    (primary.search(line) and "digital" in line and "undeclared" in line)
    or (secondary.search(line) and ("incomplete type" in line or "sizeof" in line))
    for line in errors)
# A fixed feature or any unrelated compile error makes WILL_FAIL fail.
if result.returncode != 0 and expected:
    print("Confirmed known AUX_SETTINGS_PULLUP compile defect at core/ioports.c:1446.")
    sys.exit(1)
print("Expected compile diagnostic was not reproduced; review this regression.")
sys.exit(0)
