"""Resolve a suite candidate once; every CI job consumes the immutable result."""
import argparse
import json
import os
import re
import urllib.parse
import urllib.request
from pathlib import Path


def api(repository, endpoint):
    headers = {"Accept": "application/vnd.github+json"}
    token = os.environ.get("GH_TOKEN")
    if token:
        headers["Authorization"] = "Bearer " + token
    request = urllib.request.Request(
        "https://api.github.com/repos/" + repository + "/" + endpoint, headers=headers)
    with urllib.request.urlopen(request, timeout=30) as response:
        return json.load(response)


def resolve(suite, repository="", ref="", pr="", request=api):
    if pr and ref:
        raise ValueError("Choose a PR number or a ref, not both")
    repository = repository or suite["repository"]
    if not re.fullmatch(r"[A-Za-z0-9_.-]+/[A-Za-z0-9_.-]+", repository):
        raise ValueError("Repository must be owner/name")
    if pr:
        if not pr.isdecimal() or int(pr) < 1:
            raise ValueError("PR must be a positive integer")
        pull = request(repository, "pulls/" + pr)
        repository = pull["head"]["repo"]["full_name"]
        sha = pull["head"]["sha"]
        selected = "PR " + pr + " head"
    elif ref:
        sha = request(repository, "commits/" + urllib.parse.quote(ref, safe=""))["sha"]
        selected = ref
    else:
        if repository != suite["repository"]:
            raise ValueError("A different repository requires a ref or PR")
        ref = suite["ref"]
        sha = request(repository, "commits/" + urllib.parse.quote(ref, safe=""))["sha"]
        selected = ref
    if not re.fullmatch(r"[0-9a-fA-F]{40}", sha):
        raise ValueError("GitHub did not resolve an exact commit")
    return {**suite, "repository": repository, "sha": sha, "selection": selected}


def resolve_plan(suites, suite_name, repository="", ref="", pr="", core_ref="", request=api):
    if suite_name not in suites:
        raise ValueError("Suite has no tests registered: " + suite_name)
    source = resolve(suites[suite_name], repository, ref, pr, request)
    if core_ref and "core" not in source.get("dependencies", []):
        raise ValueError("core-ref only applies to suites depending on core")
    sources = [source]
    for dependency in source.get("dependencies", []):
        sources.append(resolve(suites[dependency], ref=core_ref if dependency == "core" else "", request=request))
    paths = [item["path"] for item in sources]
    if len(paths) != len(set(paths)):
        raise ValueError("Source checkout paths must be distinct")
    source["sources"] = [{key: item[key] for key in ("repository", "sha", "path", "selection")} for item in sources]
    source["suite"] = suite_name
    return source


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--suite", default="core")
    parser.add_argument("--core-ref", default="")
    parser.add_argument("--repository", default="")
    parser.add_argument("--ref", default="")
    parser.add_argument("--pr", default="")
    args = parser.parse_args()
    suites = json.loads(Path("ci/suites.json").read_text())
    source = resolve_plan(suites, args.suite, args.repository, args.ref, args.pr, args.core_ref)
    source["harness_sha"] = os.environ.get("HARNESS_SHA", "local")
    source["harness_repository"] = os.environ.get("HARNESS_REPOSITORY", "")
    Path("source-lock.json").write_text(json.dumps(source, indent=2) + "\n")
    print(json.dumps(source, indent=2))
    if os.environ.get("GITHUB_OUTPUT"):
        with open(os.environ["GITHUB_OUTPUT"], "a") as output:
            for key in ("repository", "sha", "path", "coverage_filter"):
                output.write(key + "=" + source[key] + "\n")
    if os.environ.get("GITHUB_STEP_SUMMARY"):
        with open(os.environ["GITHUB_STEP_SUMMARY"], "a") as summary:
            summary.write("### Tested sources\n\n")
            summary.write("Test harness: `" + source["harness_sha"] + "`\n\n")
            for item in source["sources"]:
                summary.write("- " + item["repository"] + " at `" + item["sha"] +
                              "` (" + item["selection"] + ")\n")


if __name__ == "__main__":
    main()
