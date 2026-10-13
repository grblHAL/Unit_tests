import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

SCRIPTS = Path(__file__).resolve().parent

class SuiteReportingTests(unittest.TestCase):
    def run_report(self, stage, warning=False, failure=False, known=False):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "scripts").mkdir()
            for name in ("summary.py", "run_suite.py"):
                shutil.copyfile(SCRIPTS / name, root / "scripts" / name)
            (root / "build").mkdir()
            (root / "plugin-diagnostics").mkdir()
            (root / "plugin-diagnostics/known_sanitizer_diagnostics.json").write_text("[]")
            lock = {"suite": "example_plugin", "diagnostics_directory": "plugin-diagnostics", "path": "plugins/example_plugin", "harness_repository": "owner/tests", "harness_sha": "a" * 40}
            (root / "source-lock.json").write_text(json.dumps(lock))
            output = "source.c:1:1: runtime error: unexpected warning" if warning else ""
            properties = '<properties><property name="cmake_labels" value="known_bug"/></properties>' if known else ''
            failed = '<failure message="failure">fixture assertion</failure>' if failure else ''
            (root / "build/results.xml").write_text('<testsuite><testcase name="example_plugin.case">' + properties + failed + '<system-out>' + output + '</system-out></testcase></testsuite>')
            (root / "plugins/example_plugin").mkdir(parents=True)
            (root / "plugins/example_plugin/code.c").write_text("/* fixture */")
            (root / "plugins/example_plugin/new_file.c").write_text("/* uninstrumented */")
            (root / "core").mkdir()
            (root / "core/unrelated.c").write_text("/* excluded */")
            (root / "coverage.xml").write_text('<coverage><packages><package><classes><class filename="plugins/example_plugin/code.c" line-rate="1" branch-rate="1"/></classes></package></packages></coverage>')
            env = os.environ.copy()
            env.pop("GITHUB_STEP_SUMMARY", None)
            env.pop("GITHUB_ACTIONS", None)
            return subprocess.run([sys.executable, "scripts/run_suite.py", stage], cwd=root, env=env, capture_output=True, text=True)

    def test_summary_accepts_suite_specific_manifest(self):
        result = self.run_report("summary")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("example_plugin test results", result.stdout)
        self.assertIn("1 clean passes", result.stdout)

    def test_unknown_sanitizer_warning_still_fails(self):
        result = self.run_report("summary", warning=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("1 failed", result.stdout)

    def test_plugin_coverage_inventories_plugin_instead_of_core(self):
        result = self.run_report("coverage-summary")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("1 of 2 source files instrumented", result.stdout)
        self.assertIn("plugins/example_plugin/code.c", result.stdout)
        self.assertNotIn("unrelated.c", result.stdout)

    def test_known_failure_links_correct_harness_and_cleanup_guidance(self):
        result = self.run_report("summary", failure=True, known=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("it may be a fixed regression", result.stdout)
        self.assertIn("https://github.com/owner/tests/blob/" + "a" * 40 + "/plugin-diagnostics/KNOWN_BUGS.md", result.stdout)
        self.assertIn("retain the test", result.stdout)
        self.assertIn("unrelated crash", result.stdout)

    def test_general_failure_gives_reproduction_without_claiming_fixed_bug(self):
        result = self.run_report("summary", failure=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("LastTest.log", result.stdout)
        self.assertIn("intended contract", result.stdout)
        self.assertNotIn("it may be a fixed regression", result.stdout)

    def test_missing_source_reports_gap_without_claiming_new_code(self):
        result = self.run_report("coverage-summary")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("1 files are absent", result.stdout)
        self.assertIn("specified baseline", result.stdout)
        self.assertIn("check its CMake inclusion", result.stdout)

if __name__ == "__main__":
    unittest.main()
