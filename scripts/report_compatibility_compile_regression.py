"""Match only the documented missing G59.3 symbol in compatibility reporting."""
import re
import subprocess
import sys

compiler, core, source, level = sys.argv[1:]
def compile_level(value):
    return subprocess.run([compiler, "-std=c11", "-fsyntax-only", "-DCOMPATIBILITY_LEVEL=" + value,
                           "-I" + core, source], stdout=subprocess.PIPE,
                          stderr=subprocess.STDOUT, text=True)

baseline = compile_level("1")
if baseline.returncode:
    print(baseline.stdout)
    print("Compatibility level 1 baseline failed; this is not the known defect.")
    sys.exit(0)
result = compile_level(level)
print(result.stdout)
print(f"Compiler exit code: {result.returncode}")
errors = [line for line in result.stdout.splitlines() if ": error:" in line]
pattern = re.compile(r"report\.c:718:[0-9]+: error:.*")
expected = bool(errors) and all(pattern.search(line) and "CoordinateSystem_G59_3" in line
                               and "undeclared" in line for line in errors)
if result.returncode and expected:
    print(f"Confirmed known compatibility level {level} report compile defect at core/report.c:718.")
    sys.exit(1)
print("Expected compile diagnostic was not reproduced; review this regression.")
sys.exit(0)
