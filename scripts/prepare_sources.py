"""Fetch a source lock into ordinary ignored checkouts; preserve existing work."""
import argparse
import json
import re
import subprocess
from pathlib import Path


def git(*args):
    return subprocess.check_output(["git", *args], text=True).strip()


def prepare(source, root):
    relative = Path(source["path"])
    target = (root / relative).resolve()
    if relative.is_absolute() or ".." in relative.parts or not target.is_relative_to(root) or target == root:
        raise ValueError("Source path must remain inside the workspace")
    repository, sha = source["repository"], source["sha"]
    if not re.fullmatch(r"[A-Za-z0-9_.-]+/[A-Za-z0-9_.-]+", repository) or not re.fullmatch(r"[0-9a-fA-F]{40}", sha):
        raise ValueError("Invalid repository or commit in source lock")
    if target.exists():
        if not (target / ".git").exists():
            raise ValueError("Existing source directory is not a checkout: " + str(target))
        if git("-C", str(target), "status", "--porcelain"):
            raise ValueError("Preserve local source changes before fetching: " + str(target))
        if git("-C", str(target), "rev-parse", "HEAD") != sha:
            raise ValueError("Existing source differs; switch it explicitly or use a fresh checkout: " + str(target))
        return
    target.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(["git", "init", str(target)], check=True)
    subprocess.run(["git", "-C", str(target), "remote", "add", "origin", "https://github.com/" + repository + ".git"], check=True)
    subprocess.run(["git", "-C", str(target), "fetch", "--depth=1", "origin", sha], check=True)
    subprocess.run(["git", "-C", str(target), "checkout", "--detach", "FETCH_HEAD"], check=True)
    if git("-C", str(target), "rev-parse", "HEAD") != sha:
        raise ValueError("Fetched commit does not match source lock")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--lock", default="source-lock.json")
    args = parser.parse_args()
    lock = json.loads(Path(args.lock).read_text())
    for source in lock["sources"]:
        prepare(source, Path.cwd().resolve())


if __name__ == "__main__":
    main()
