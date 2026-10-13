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
    def run_report(self, stage, warning=False):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "scripts").mkdir()
            for name in ("summary.py", "run_suite.py"):
                shutil.copyfile(SCRIPTS / name, root / "scripts" / name)
            (root / "build").mkdir()
            (root / "plugin-diagnostics").mkdir()
            (root / "plugin-diagnostics/known_sanitizer_diagnostics.json").write_text("[]")
            lock = {"suite": "example_plugin", "diagnostics_directory": "plugin-diagnostics", "path": "plugins/example_plugin"}
            (root / "source-lock.json").write_text(json.dumps(lock))
            output = "source.c:1:1: runtime error: unexpected warning" if warning else ""
            (root / "build/results.xml").write_text('<testsuite><testcase name="example_plugin.case"><system-out>' + output + '</system-out></testcase></testsuite>')
            (root / "plugins/example_plugin").mkdir(parents=True)
            (root / "plugins/example_plugin/code.c").write_text("/* fixture */")
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
        self.assertIn("1 of 1 source files instrumented", result.stdout)
        self.assertIn("plugins/example_plugin/code.c", result.stdout)
        self.assertNotIn("unrelated.c", result.stdout)

if __name__ == "__main__":
    unittest.main()
