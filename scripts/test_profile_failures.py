import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
import xml.etree.ElementTree as ET
from ci_report import test_findings

SCRIPTS = Path(__file__).resolve().parent

class ProfileFailuresTests(unittest.TestCase):
    def test_both_reports_reject_counter_failures_even_for_known_tests(self):
        messages = ["profiling: /repo/build/case.gcda: cannot open: No such file or directory",
                    "libgcov profiling error:/repo/build/case.gcda:overwriting an existing profile data with a different checksum",
                    "Controller job completed"]
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "known_sanitizer_diagnostics.json").write_text("[]")
            path = root / "results.xml"
            for message in messages:
                with self.subTest(message=message):
                    failure = message != "Controller job completed"
                    tree = ET.Element("testsuite")
                    case = ET.SubElement(tree, "testcase", name="component.case")
                    properties = ET.SubElement(case, "properties")
                    ET.SubElement(properties, "property", name="cmake_labels", value="known_bug")
                    ET.SubElement(case, "system-out").text = message
                    ET.ElementTree(tree).write(path)
                    findings, counts = test_findings(path, root)
                    self.assertEqual(counts["failed"], int(failure))
                    if failure:
                        self.assertEqual(findings[0]["kind"], "coverage")
                    environment = {key: value for key, value in os.environ.items() if key != "GITHUB_STEP_SUMMARY"}
                    result = subprocess.run([sys.executable, str(SCRIPTS / "summary.py"), "tests", str(path), "--diagnostics-directory", str(root)],
                                            cwd=root, env=environment, capture_output=True, text=True)
                    self.assertEqual(result.returncode, int(failure), result.stderr + result.stdout)
                    if failure:
                        self.assertIn("Coverage counter data could not be saved", result.stdout)
                        self.assertNotIn("Known regression changed", result.stdout)
