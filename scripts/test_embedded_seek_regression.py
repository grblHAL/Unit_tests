"""Ensure the known-memory matcher cannot hide a fix or an unrelated fault."""
import contextlib
import io
from pathlib import Path
import runpy
import subprocess
import unittest
from unittest.mock import patch

class EmbeddedSeekMatcherTests(unittest.TestCase):
    def classify(self, output, returncode=1):
        result = subprocess.CompletedProcess([], returncode, stdout=output)
        with patch("sys.argv", ["embedded_seek_regression.py", "1", "fixture"]), patch("subprocess.run", return_value=result), contextlib.redirect_stdout(io.StringIO()):
            with self.assertRaises(SystemExit) as exit_result:
                runpy.run_path(str(Path(__file__).with_name("embedded_seek_regression.py")), run_name="__main__")
        return exit_result.exception.code

    def test_verified_overread_is_recognized(self):
        self.assertEqual(self.classify("READ of size 8\nSUMMARY: AddressSanitizer: global-buffer-overflow /checkout/core/fs_embedded.c:122:95 in fs_seek"), 1)

    def test_fixed_executable_requires_exception_cleanup(self):
        self.assertEqual(self.classify("", returncode=0), 0)

    def test_other_source_fault_is_rejected(self):
        self.assertEqual(self.classify("READ of size 8\nSUMMARY: AddressSanitizer: global-buffer-overflow /checkout/core/gcode.c:122:95"), 0)

    def test_different_embedded_fault_is_rejected(self):
        self.assertEqual(self.classify("READ of size 8\nSUMMARY: AddressSanitizer: global-buffer-overflow /checkout/core/fs_embedded.c:123:95"), 0)
