import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch
import xml.etree.ElementTree as ET
from ci_report import test_findings

SCRIPTS = Path(__file__).resolve().parent

class SanitizerExpectationTests(unittest.TestCase):
    def reports(self, output="", label=True, failure=False, name="module.case", stderr_output="", manifest=None):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            manifest = manifest if manifest is not None else [{"test": "module.case", "source": "core/code.c", "lines": [7], "message_pattern": "negation of minimum"}]
            (root / "known_sanitizer_diagnostics.json").write_text(json.dumps(manifest))
            suite = ET.Element("testsuite")
            case = ET.SubElement(suite, "testcase", name=name)
            if label:
                properties = ET.SubElement(case, "properties")
                ET.SubElement(properties, "property", name="cmake_labels", value=label if isinstance(label, str) else "known_sanitizer_bug")
            if failure:
                ET.SubElement(case, "failure", message="Correct assertion failed")
            ET.SubElement(case, "system-out").text = output
            ET.SubElement(case, "system-err").text = stderr_output
            results = root / "results.xml"
            ET.ElementTree(suite).write(results)
            findings, counts = test_findings(results, root)
            env = os.environ.copy()
            env.pop("GITHUB_STEP_SUMMARY", None)
            env.pop("GITHUB_ACTIONS", None)
            summary = subprocess.run([sys.executable, str(SCRIPTS / "summary.py"), "tests", str(results), "--diagnostics-directory", str(root)], cwd=root, env=env, capture_output=True, text=True)
            return findings, counts, summary

    def test_absent_axis_manifest_accepts_exact_gcc_and_clang_type_spellings(self):
        manifest = json.loads((SCRIPTS.parent / "tests/known_sanitizer_diagnostics.json").read_text())
        for width, spelling in [(32, "unsigned long"), (64, "unsigned long"), (64, "long unsigned int")]:
            with self.subTest(width=width, spelling=spelling):
                output = f"/repo/core/ngc_params.c:177:45: runtime error: shift exponent 255 is too large for {width}-bit type '{spelling}'"
                findings, counts, summary = self.reports(output,
                    name="eight_axis.absent_named_w_position_in_inches_returns_zero", manifest=manifest)
                self.assertEqual(findings, [])
                self.assertEqual(counts["known"], 1)
                self.assertEqual(summary.returncode, 0, summary.stderr)

    def test_absent_axis_manifest_rejects_other_shift_or_source(self):
        manifest = json.loads((SCRIPTS.parent / "tests/known_sanitizer_diagnostics.json").read_text())
        for source, exponent in [("core/ngc_params.c:178", 255), ("core/other.c:177", 255), ("core/ngc_params.c:177", 254)]:
            with self.subTest(source=source, exponent=exponent):
                output = f"/repo/{source}:45: runtime error: shift exponent {exponent} is too large for 64-bit type 'long unsigned int'"
                findings, counts, summary = self.reports(output,
                    name="eight_axis.absent_named_w_position_in_inches_returns_zero", manifest=manifest)
                self.assertEqual(counts["failed"], 1)
                self.assertNotEqual(summary.returncode, 0)

    def test_matching_scoped_diagnostic_is_known(self):
        findings, counts, summary = self.reports("/repo/core/code.c:7:1: runtime error: negation of minimum")
        self.assertEqual(findings, [])
        self.assertEqual(counts["known"], 1)
        self.assertEqual(summary.returncode, 0, summary.stderr)
        self.assertIn("1 passed with known sanitizer diagnostics", summary.stdout)

    def test_parent_actions_environment_does_not_redirect_fixture_summary(self):
        with tempfile.TemporaryDirectory() as directory:
            target = Path(directory) / "parent-summary.md"
            with patch.dict(os.environ, {"GITHUB_STEP_SUMMARY": str(target), "GITHUB_ACTIONS": "true"}):
                findings, counts, summary = self.reports("/repo/core/code.c:7:1: runtime error: negation of minimum")
            self.assertEqual(findings, [])
            self.assertEqual(summary.returncode, 0, summary.stderr)
            self.assertIn("1 passed with known sanitizer diagnostics", summary.stdout)
            self.assertFalse(target.exists())

    def test_fixed_diagnostic_requires_exception_cleanup(self):
        findings, counts, summary = self.reports()
        self.assertEqual(counts["failed"], 1)
        self.assertEqual(findings[0]["kind"], "known_changed")
        self.assertIn("no longer reproduced", findings[0]["message"])
        self.assertNotEqual(summary.returncode, 0)
        self.assertIn("it may be a fixed regression", summary.stdout)
        self.assertIn("retain the test", summary.stdout)

    def test_manifest_does_not_accept_another_test(self):
        findings, counts, summary = self.reports("/repo/core/code.c:7:1: runtime error: negation of minimum", name="other.case", label=False)
        self.assertEqual(counts["failed"], 1)
        self.assertEqual(findings[0]["kind"], "sanitizer")
        self.assertNotEqual(summary.returncode, 0)

    def test_different_diagnostic_is_not_hidden(self):
        findings, counts, summary = self.reports("/repo/core/code.c:7:1: runtime error: different overflow")
        self.assertEqual(counts["failed"], 1)
        self.assertIn("different overflow", findings[0]["message"])
        self.assertNotEqual(summary.returncode, 0)

    def test_assertion_failure_is_not_relabelled_missing_diagnostic(self):
        findings, counts, summary = self.reports("Correct assertion failed", failure=True)
        self.assertEqual(counts["failed"], 1)
        self.assertIn("Correct assertion failed", findings[0]["message"])
        self.assertNotIn("no longer reproduced", findings[0]["message"])
        self.assertNotEqual(summary.returncode, 0)

    def test_expected_failure_label_does_not_hide_new_asan_crash(self):
        findings, counts, summary = self.reports(
            "ERROR: AddressSanitizer: access-violation", label="known_bug")
        self.assertEqual(counts["failed"], 1)
        self.assertEqual(counts["known"], 0)
        self.assertEqual(findings[0]["kind"], "known_changed")
        self.assertNotEqual(summary.returncode, 0)
        self.assertIn("0 known regressions reproduced", summary.stdout)
        self.assertIn("0 clean passes", summary.stdout)
        self.assertIn("Unexpected sanitizer diagnostic", summary.stdout)

    def test_expected_failure_label_does_not_hide_new_ubsan_fault(self):
        findings, counts, summary = self.reports(
            "/repo/core/code.c:8:1: runtime error: null pointer passed", label="known_bug")
        self.assertEqual(counts["failed"], 1)
        self.assertEqual(counts["known"], 0)
        self.assertNotEqual(summary.returncode, 0)
        self.assertIn("null pointer passed", findings[0]["message"])

    def test_stderr_sanitizer_crash_on_expected_failure_is_not_hidden(self):
        findings, counts, summary = self.reports(label="known_bug",
            stderr_output="ERROR: AddressSanitizer: attempting free on invalid pointer")
        self.assertEqual(counts["failed"], 1)
        self.assertNotEqual(summary.returncode, 0)
        self.assertIn("invalid pointer", findings[0]["message"])

    def test_expected_assertion_failure_without_new_diagnostic_remains_known(self):
        findings, counts, summary = self.reports("Correct regression assertion failed", label="known_bug")
        self.assertEqual(findings, [])
        self.assertEqual(counts["known"], 1)
        self.assertEqual(summary.returncode, 0, summary.stderr)
        self.assertIn("1 known regressions reproduced", summary.stdout)

    def test_uninstrumented_case_needs_no_diagnostic(self):
        findings, counts, summary = self.reports(label=False)
        self.assertEqual(findings, [])
        self.assertEqual(counts["clean"], 1)
        self.assertEqual(summary.returncode, 0, summary.stderr)

if __name__ == "__main__":
    unittest.main()
