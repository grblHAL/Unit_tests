import unittest
from unittest.mock import patch
from resolve_source import resolve

SHA = "a" * 40
SUITE = {"repository": "grblHAL/core", "path": "core", "coverage_filter": "core/.*"}

class SourceResolutionTests(unittest.TestCase):
    def test_baseline_uses_recorded_pin_without_network(self):
        with patch("resolve_source.subprocess.check_output", return_value="160000 commit " + SHA + "\tcore\n"):
            self.assertEqual(resolve(SUITE, request=lambda *args: self.fail("network"))["sha"], SHA)

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

if __name__ == "__main__":
    unittest.main()
