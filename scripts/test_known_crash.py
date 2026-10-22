import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
import xml.etree.ElementTree as ET

from unittest.mock import patch
from known_crash import matches_known_crash, main
from ci_report import test_findings

SCRIPTS = Path(__file__).resolve().parent
NAME = "module.case"
MANIFEST = [dict(kind="fatal_asan", test=NAME, source="core/vfs.c", lines=[509],
                 function="vfs_chdir", message_pattern="access-violation")]
OUTPUT = """==1==ERROR: AddressSanitizer: access-violation on unknown address
    #0 0x123 in vfs_chdir /repo/core/vfs.c:509:20
SUMMARY: AddressSanitizer: access-violation /repo/core/vfs.c:509:20 in vfs_chdir
"""


class KnownCrashTests(unittest.TestCase):
    def test_exact_diagnostic_matches_both_path_styles(self):
        self.assertTrue(matches_known_crash(NAME, OUTPUT, MANIFEST))
        self.assertTrue(matches_known_crash(NAME, OUTPUT.replace("/", "\\"), MANIFEST))

    def test_other_test_source_line_frame_and_fault_are_rejected(self):
        self.assertFalse(matches_known_crash("other.case", OUTPUT, MANIFEST))
        for original, replacement in [("509", "510"), ("vfs.c", "other.c"),
                                       ("#0", "#1"), ("access-violation", "heap-use-after-free")]:
            self.assertFalse(matches_known_crash(NAME, OUTPUT.replace(original, replacement), MANIFEST))

    def test_extra_sanitizer_fault_is_rejected(self):
        self.assertFalse(matches_known_crash(NAME, OUTPUT + OUTPUT, MANIFEST))
        self.assertFalse(matches_known_crash(NAME, OUTPUT + "ERROR: LeakSanitizer: leak", MANIFEST))
        self.assertFalse(matches_known_crash(NAME, OUTPUT + "other.c:1:1: runtime error: overflow", MANIFEST))

    def test_reports_keep_exact_crash_known_and_changed_fault_red(self):
        import os
        for output, failed in [(OUTPUT, False), (OUTPUT.replace("509", "510"), True), ("", True)]:
            with self.subTest(failed=failed), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                (root / "known_sanitizer_diagnostics.json").write_text(json.dumps(MANIFEST))
                suite = ET.Element("testsuite")
                case = ET.SubElement(suite, "testcase", name=NAME)
                props = ET.SubElement(case, "properties")
                ET.SubElement(props, "property", name="cmake_labels", value="known_bug;known_crash")
                ET.SubElement(case, "system-out").text = output
                result = root / "results.xml"
                ET.ElementTree(suite).write(result)
                findings, counts = test_findings(result, root)
                self.assertEqual(counts["failed"], int(failed))
                self.assertEqual(counts["known"], int(not failed))
                env = os.environ.copy()
                env.pop("GITHUB_STEP_SUMMARY", None)
                env.pop("GITHUB_ACTIONS", None)
                summary = subprocess.run([sys.executable, str(SCRIPTS / "summary.py"), "tests", str(result),
                                          "--diagnostics-directory", str(root)], env=env, capture_output=True)
                self.assertEqual(summary.returncode != 0, failed, summary.stderr)

    def test_runner_accepts_only_nonzero_exact_reproduction(self):
        for code, output, expected in [(1, OUTPUT, 1), (0, OUTPUT, 0),
                                        (1, OUTPUT.replace("509", "510"), 0), (1, "assertion failed", 0)]:
            with self.subTest(code=code, output=output), patch("sys.argv", ["runner", NAME, "inventory", "executable"]), \
                    patch("known_crash.Path.read_text", return_value=json.dumps(MANIFEST)), \
                    patch("known_crash.Path.write_text"), patch("builtins.print"), \
                    patch("known_crash.subprocess.run", return_value=subprocess.CompletedProcess([], code, output)):
                self.assertEqual(main(), expected)

    def test_linux_core_segv_requires_the_same_source_and_frame(self):
        manifest = [dict(MANIFEST[0], message_pattern="(?:access-violation|SEGV)")]
        self.assertTrue(matches_known_crash(NAME, OUTPUT.replace("access-violation", "SEGV"), manifest))
        self.assertFalse(matches_known_crash(NAME, OUTPUT.replace("access-violation", "SEGV").replace("509", "510"), manifest))

    def test_gcc_zero_pc_requires_exact_recorded_caller_chain(self):
        output = """ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x000000000000 bp 0x123)
    #0 0x0  (<unknown module>)
    #1 0x123 in engine_execute_tasks /repo/tests/support/task_host.c:8
    #2 0x456 in main /repo/tests/cases/grbllib/irq.c:27
SUMMARY: AddressSanitizer: SEGV (<unknown module>)
"""
        manifest = [dict(MANIFEST[0], zero_pc_frames=[
            dict(function="engine_execute_tasks", source="tests/support/task_host.c", line=8),
            dict(function="main", source="tests/cases/grbllib/irq.c", line=27)])]
        self.assertTrue(matches_known_crash(NAME, output, manifest))
        for before, after in [("pc 0x000000000000", "pc 0x123456789012"),
                              ("task_host.c:8", "task_host.c:9"), ("irq.c:27", "other.c:27"),
                              ("#2", "#3"), ("engine_execute_tasks", "other_callback")]:
            self.assertFalse(matches_known_crash(NAME, output.replace(before, after), manifest))
        self.assertFalse(matches_known_crash("other.case", output, manifest))
        self.assertFalse(matches_known_crash(NAME, output + "ERROR: AddressSanitizer: heap-use-after-free", manifest))
        self.assertFalse(matches_known_crash(NAME, output + "other.c:1:1: runtime error: overflow", manifest))

    def test_recorded_ubsan_prelude_requires_exact_index_source_and_line(self):
        runtime = "/repo/core/vfs.c:509:20: runtime error: index -1 out of bounds for type 'entry_t[20]'\n"
        summary = "SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior /repo/core/vfs.c:509:20 \n"
        manifest = [dict(MANIFEST[0], preceding_ubsan_pattern=r"index -1 out of bounds for type 'entry_t\[20\]'")]
        self.assertTrue(matches_known_crash(NAME, runtime + summary + OUTPUT, manifest))
        self.assertTrue(matches_known_crash(NAME, runtime + OUTPUT, manifest))
        for output in [OUTPUT, runtime + runtime + OUTPUT, runtime.replace("-1", "-2") + OUTPUT,
                       runtime.replace("509", "510") + OUTPUT, runtime.replace("vfs.c", "other.c") + OUTPUT,
                       runtime + summary.replace("509", "510") + OUTPUT, runtime + summary + summary + OUTPUT,
                       runtime + OUTPUT + "other.c:1:1: runtime error: overflow"]:
            self.assertFalse(matches_known_crash(NAME, output, manifest), output)
        self.assertFalse(matches_known_crash(NAME, runtime + summary + OUTPUT, MANIFEST))

    def test_gcc_asan_frames_can_omit_column_with_exact_ubsan_source(self):
        runtime = "/repo/core/vfs.c:509:20: runtime error: index -1 out of bounds for type 'entry_t [20]'\n"
        manifest = [dict(MANIFEST[0], preceding_ubsan_pattern=r"index -1 out of bounds for type 'entry_t ?\[20\]'")]
        output = runtime + OUTPUT.replace(":509:20", ":509")
        self.assertTrue(matches_known_crash(NAME, output, manifest))
        for changed in [output.replace(":509 in", ":510 in"),
                        output.replace(":509:20: runtime", ":510:20: runtime"),
                        output.replace("vfs.c", "other.c"),
                        output.replace("in vfs_chdir", "in other_function"),
                        output + "other.c:1:1: runtime error: overflow"]:
            self.assertFalse(matches_known_crash(NAME, changed, manifest), changed)

    def test_runner_error_is_not_an_expected_failure(self):
        result = subprocess.run([sys.executable, str(SCRIPTS / "known_crash.py"), NAME,
                                 "missing-inventory.json", "missing-executable"], capture_output=True)
        self.assertEqual(result.returncode, 0)
        self.assertIn(b"runner failed", result.stdout)


if __name__ == "__main__":
    unittest.main()
