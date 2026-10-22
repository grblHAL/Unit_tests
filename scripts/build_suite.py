"""Build independent targets after an error, preserving the build failure."""
import argparse
from pathlib import Path
import subprocess
import sys


def build_command(directory, parallel):
    cache = (Path(directory) / "CMakeCache.txt").read_text(encoding="utf-8")
    generator = next(line.split("=", 1)[1] for line in cache.splitlines()
                     if line.startswith("CMAKE_GENERATOR:INTERNAL="))
    command = ["cmake", "--build", str(directory), "--parallel", str(parallel)]
    if generator in ("Ninja", "Ninja Multi-Config"):
        command += ["--", "-k", "0"]
    elif generator in ("Unix Makefiles", "MinGW Makefiles", "MSYS Makefiles"):
        command += ["--", "-k"]
    return command


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--build-dir", default="build")
    parser.add_argument("--parallel", type=int, default=2)
    args = parser.parse_args()
    return subprocess.run(build_command(args.build_dir, args.parallel)).returncode


if __name__ == "__main__":
    sys.exit(main())
