"""Configure the registered suite without shell-evaluating caller inputs."""
import argparse
import json
import subprocess
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument("--mode", choices=("sanitizers", "coverage"), required=True)
parser.add_argument("--compiler", choices=("gcc", "clang"), required=True)
args = parser.parse_args()
lock = json.loads(Path("source-lock.json").read_text())
command = ["cmake", "-S", lock["cmake_source"], "-B", "build", "-DCMAKE_BUILD_TYPE=Debug",
           "-DCMAKE_C_COMPILER=" + args.compiler]
command += lock["cmake_options"]
command += ["-DENABLE_SANITIZERS=ON"] if args.mode == "sanitizers" else ["-DENABLE_COVERAGE=ON"]
subprocess.run(command, check=True)
