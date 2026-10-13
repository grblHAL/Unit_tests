import argparse
import json
import subprocess
import sys
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument("stage", choices=("test", "summary", "coverage-summary"))
args = parser.parse_args()
lock = json.loads(Path("source-lock.json").read_text())
if args.stage == "test":
    command = ["ctest", "--test-dir", "build", "--output-on-failure",
               "--output-junit", "results.xml", "--no-tests=error", "-R", lock["test_regex"]]
elif args.stage == "summary":
    command = [sys.executable, "scripts/summary.py", "tests", "build/results.xml",
               "--diagnostics-directory", lock["diagnostics_directory"],
               "--suite-name", lock["suite"]]
else:
    command = [sys.executable, "scripts/summary.py", "coverage", "coverage.xml",
               "--source-directory", lock["path"], "--suite-name", lock["suite"]]
subprocess.run(command, check=True)
