import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch
from prepare_sources import prepare

class PrepareSourceTests(unittest.TestCase):
    def source(self, path="core"):
        return {"repository": "grblHAL/core", "sha": "a" * 40, "path": path}

    def test_path_escape_is_rejected_before_git(self):
        with tempfile.TemporaryDirectory() as directory, patch("prepare_sources.git") as git:
            with self.assertRaises(ValueError):
                prepare(self.source("../outside"), Path(directory).resolve())
            git.assert_not_called()

    def test_existing_non_checkout_is_preserved(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory).resolve()
            (root / "core").mkdir()
            marker = root / "core/local.txt"
            marker.write_text("preserve")
            with self.assertRaises(ValueError):
                prepare(self.source(), root)
            self.assertEqual(marker.read_text(), "preserve")

    def test_dirty_checkout_is_preserved(self):
        with tempfile.TemporaryDirectory() as directory, patch("prepare_sources.git", return_value=" M source.c"), patch("prepare_sources.subprocess.run") as run:
            root = Path(directory).resolve()
            (root / "core/.git").mkdir(parents=True)
            with self.assertRaises(ValueError):
                prepare(self.source(), root)
            run.assert_not_called()

    def test_different_revision_requires_explicit_user_switch(self):
        with tempfile.TemporaryDirectory() as directory, patch("prepare_sources.git", side_effect=["", "b" * 40]), patch("prepare_sources.subprocess.run") as run:
            root = Path(directory).resolve()
            (root / "core/.git").mkdir(parents=True)
            with self.assertRaises(ValueError):
                prepare(self.source(), root)
            run.assert_not_called()

    def test_new_checkout_fetches_exact_sha(self):
        with tempfile.TemporaryDirectory() as directory, patch("prepare_sources.git", return_value="a" * 40), patch("prepare_sources.subprocess.run") as run:
            root = Path(directory).resolve()
            prepare(self.source(), root)
            self.assertEqual(run.call_args_list[2].args[0][-3:], ["--depth=1", "origin", "a" * 40])

if __name__ == "__main__":
    unittest.main()
