import unittest
from resolve_source import resolve, resolve_plan

SHA = "a" * 40
SUITE = {"repository": "grblHAL/core", "path": "core", "ref": "master", "coverage_filter": "core/.*"}

class SourceResolutionTests(unittest.TestCase):
    def test_default_resolves_configured_branch(self):
        def request(repo, endpoint):
            self.assertEqual((repo, endpoint), ("grblHAL/core", "commits/master"))
            return {"sha": SHA}
        self.assertEqual(resolve(SUITE, request=request)["sha"], SHA)

    def test_branch_resolves_once_and_encodes_slashes(self):
        calls = []
        def request(repo, endpoint):
            calls.append((repo, endpoint))
            return {"sha": SHA}
        result = resolve(SUITE, ref="feature/fix", request=request)
        self.assertEqual(calls, [("grblHAL/core", "commits/feature%2Ffix")])
        self.assertEqual(result["sha"], SHA)

    def test_fork_pr_uses_actual_head_repo_and_commit(self):
        def request(repo, endpoint):
            self.assertEqual((repo, endpoint), ("grblHAL/core", "pulls/42"))
            return {"head": {"repo": {"full_name": "contributor/core"}, "sha": SHA}}
        result = resolve(SUITE, pr="42", request=request)
        self.assertEqual((result["repository"], result["sha"]), ("contributor/core", SHA))

    def test_fork_branch_does_not_require_upstream_commit(self):
        def request(repo, endpoint):
            self.assertEqual(repo, "contributor/core")
            return {"sha": SHA}
        self.assertEqual(resolve(SUITE, "contributor/core", "fix", request=request)["sha"], SHA)

    def test_ambiguous_selection_is_rejected(self):
        with self.assertRaises(ValueError):
            resolve(SUITE, ref="master", pr="42")

    def test_different_repo_without_revision_is_rejected(self):
        with self.assertRaises(ValueError):
            resolve(SUITE, "contributor/core")

    def test_non_commit_response_is_rejected(self):
        with self.assertRaises(ValueError):
            resolve(SUITE, ref="master", request=lambda *args: {"sha": "master"})

class DependencyPlanTests(unittest.TestCase):
    def test_plugin_candidate_and_core_are_locked_independently(self):
        suites = {"core": SUITE, "fixture": {"repository": "owner/plugin", "ref": "master", "path": "plugins/fixture", "dependencies": ["core"]}}
        calls = []
        def request(repo, endpoint):
            calls.append((repo, endpoint))
            return {"sha": ("a" if repo == "owner/plugin" else "b") * 40}
        lock = resolve_plan(suites, "fixture", ref="fix", core_ref="next", request=request)
        self.assertEqual(calls, [("owner/plugin", "commits/fix"), ("grblHAL/core", "commits/next")])
        self.assertEqual([source["sha"] for source in lock["sources"]], ["a" * 40, "b" * 40])

    def test_unknown_suite_does_not_fall_back_to_core(self):
        with self.assertRaises(ValueError):
            resolve_plan({"core": SUITE}, "missing")

if __name__ == "__main__":
    unittest.main()
