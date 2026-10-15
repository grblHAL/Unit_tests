"""Warn about unexercised added executable lines against a locked source base."""
from pathlib import Path
import re
import subprocess
import xml.etree.ElementTree as ET
from ci_report import finding


def added_lines(diff):
    result = {}
    path = None
    line = 0
    for text in diff.splitlines():
        if text.startswith("+++ b/"):
            path = text[6:]
            result.setdefault(path, set())
        elif text.startswith("@@"):
            line = int(re.search(r"\+(\d+)", text)[1])
        elif path and text.startswith("+"):
            result[path].add(line)
            line += 1
        elif text.startswith(" "):
            line += 1
    return {p: lines for p, lines in result.items() if lines}


def coverage_lines(path):
    measured = {}
    for cls in ET.parse(path).getroot().iter("class"):
        filename = cls.get("filename", "").replace("\\", "/")
        values = measured.setdefault(filename, {})
        for line in cls.findall("./lines/line"):
            number = int(line.get("number"))
            values[number] = max(values.get(number, 0), int(line.get("hits", "0")))
    return measured


def assess(lock, coverage):
    comparison = lock.get("comparison")
    if not comparison:
        return [finding("coverage_unavailable", "Changed-code coverage not assessed", "No source baseline supplied. Use a source PR or source_base_ref; overall coverage is not evidence about new code.", severity="warning")]
    if not coverage.exists():
        return [finding("coverage_unavailable", "Changed-code coverage unavailable", "Coverage was not produced; fix earlier build/test failures before assessing new code.", severity="warning")]
    root = Path(lock["path"])
    def git(*args):
        return subprocess.check_output(["git", "-C", str(root), *args], text=True, stderr=subprocess.STDOUT).strip()
    try:
        if git("rev-parse", "--is-shallow-repository") == "true":
            git("fetch", "--unshallow", "origin", lock["sha"])
        try:
            git("cat-file", "-e", comparison["sha"] + "^{commit}")
        except subprocess.CalledProcessError:
            git("fetch", "--no-tags", "https://github.com/" + comparison["repository"] + ".git", comparison["sha"])
        base = git("merge-base", "HEAD", comparison["sha"])
        changed = added_lines(git("diff", "--unified=0", "--no-renames", "--diff-filter=AM", base, "HEAD", "--", "*.c", "*.h"))
    except subprocess.CalledProcessError:
        return [finding("coverage_unavailable", "Changed-code coverage unavailable", "Could not fetch baseline history or find a merge base. Check baseline repository/SHA and reachability.", severity="warning")]
    measured = coverage_lines(coverage)
    findings = []
    for relative, added in changed.items():
        filename = root.as_posix().rstrip("/") + "/" + relative
        if not re.search(lock["coverage_filter"], filename):
            continue
        values = measured.get(filename)
        if values is None:
            findings.append(finding("unmeasured", "Changed file absent from coverage", filename + ": check suite CMake inclusion and feature flags; absence is not proof of missing tests.", filename + ":" + str(min(added)), "warning"))
        else:
            missed = sorted(n for n in added if n in values and values[n] == 0)
            if missed:
                item = finding("uncovered", "Uncovered added executable lines", filename + ": " + str(len(missed)) + " unexercised added lines (" + ", ".join(map(str, missed[:15])) + "). Add behavioral/error-path tests.", filename + ":" + str(missed[0]), "warning")
                item["uncovered_lines"] = missed
                findings.append(item)
    return findings
