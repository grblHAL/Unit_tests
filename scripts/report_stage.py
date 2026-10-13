"""Capture each command's first meaningful error without losing its exit code."""
import argparse
import json
import os
from pathlib import Path
import subprocess
import sys
from ci_report import build_failure

p = argparse.ArgumentParser()
p.add_argument("--job", required=True)
p.add_argument("--stage", required=True)
p.add_argument("command", nargs=argparse.REMAINDER)
a = p.parse_args()
command = a.command[1:] if a.command and a.command[0] == "--" else a.command
Path("logs").mkdir(exist_ok=True)
log = Path("logs") / (a.job + "-" + a.stage + ".log")
try:
    with log.open("w", encoding="utf-8") as stream:
        environment = os.environ.copy()
        if a.stage == "classify":
            environment.pop("GITHUB_STEP_SUMMARY", None)
        process = subprocess.Popen(command, env=environment, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace")
        for line in process.stdout:
            stream.write(line)
        code = process.wait()
except OSError as error:
    log.write_text(str(error))
    code = 1
path = Path("report-" + a.job + ".json")
report = json.loads(path.read_text()) if path.exists() else dict(job=a.job, stages=[], findings=[])
report["stages"].append(dict(stage=a.stage, exit_code=code, log=log.as_posix()))
if code and a.stage not in ("test", "classify"):
    report["findings"].append(build_failure(a.stage, log.read_text(errors="replace")))
path.write_text(json.dumps(report, indent=2) + "\n")
print(a.stage + (" passed" if code == 0 else " failed; " + (report["findings"][-1]["message"] if a.stage not in ("test", "classify") else "see concise test report")) + ". Full output: " + str(log))
sys.exit(code)
