import argparse
import json
import subprocess
import sys
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument("stage", choices=("test", "summary"))
args = parser.parse_args()
lock = json.loads(Path("source-lock.json").read_text())
if args.stage == "test":
    command = ["ctest", "--test-dir", "build", "--output-on-failure",
               "--output-junit", "results.xml", "-R", lock["test_regex"]]
else:
    command = [sys.executable, "scripts/summary.py", "tests",
               lock["diagnostics_directory"], "build/results.xml"]
subprocess.run(command, check=True)
