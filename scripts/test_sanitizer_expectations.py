import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
import xml.etree.ElementTree as ET
from ci_report import test_findings

SCRIPTS = Path(__file__).resolve().parent

class SanitizerExpectationTests(unittest.TestCase):
    def reports(self, output="", label=True, failure=False, name="module.case"):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            manifest = [{"test": "module.case", "source": "core/code.c", "lines": [7], "message_pattern": "negation of minimum"}]
            (root / "known_sanitizer_diagnostics.json").write_text(json.dumps(manifest))
            suite = ET.Element("testsuite")
            case = ET.SubElement(suite, "testcase", name=name)
            if label:
                properties = ET.SubElement(case, "properties")
                ET.SubElement(properties, "property", name="cmake_labels", value="known_sanitizer_bug")
            if failure:
                ET.SubElement(case, "failure", message="Correct assertion failed")
            ET.SubElement(case, "system-out").text = output
            results = root / "results.xml"
            ET.ElementTree(suite).write(results)
            findings, counts = test_findings(results, root)
            summary = subprocess.run([sys.executable, str(SCRIPTS / "summary.py"), "tests", str(results), "--diagnostics-directory", str(root)], cwd=root, capture_output=True, text=True)
            return findings, counts, summary

    def test_matching_scoped_diagnostic_is_known(self):
        findings, counts, summary = self.reports("/repo/core/code.c:7:1: runtime error: negation of minimum")
        self.assertEqual(findings, [])
        self.assertEqual(counts["known"], 1)
        self.assertEqual(summary.returncode, 0, summary.stderr)
        self.assertIn("1 passed with known sanitizer diagnostics", summary.stdout)

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

    def test_uninstrumented_case_needs_no_diagnostic(self):
        findings, counts, summary = self.reports(label=False)
        self.assertEqual(findings, [])
        self.assertEqual(counts["clean"], 1)
        self.assertEqual(summary.returncode, 0, summary.stderr)

if __name__ == "__main__":
    unittest.main()
