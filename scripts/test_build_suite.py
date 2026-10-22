import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch
import xml.etree.ElementTree as ET
from build_suite import build_command, main

SCRIPTS = Path(__file__).resolve().parent


class BuildSuiteTests(unittest.TestCase):
    def command(self, generator):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "CMakeCache.txt").write_text("CMAKE_GENERATOR:INTERNAL=" + generator + "\n")
            return build_command(root, 3)

    def test_keep_going_matches_native_generator(self):
        self.assertEqual(self.command("Ninja")[-3:], ["--", "-k", "0"])
        self.assertEqual(self.command("Unix Makefiles")[-2:], ["--", "-k"])
        self.assertEqual(self.command("MinGW Makefiles")[-2:], ["--", "-k"])
        self.assertNotIn("--", self.command("Visual Studio 17 2022"))

    def test_build_exit_code_is_preserved(self):
        with patch("sys.argv", ["build_suite"]), patch("build_suite.build_command", return_value=["cmake"]), \
                patch("build_suite.subprocess.run", return_value=subprocess.CompletedProcess([], 7)):
            self.assertEqual(main(), 7)

    @unittest.skipUnless(shutil.which("cmake") and shutil.which("ctest") and
                         (shutil.which("ninja") or shutil.which("make")), "CMake/native build tools unavailable")
    def test_failed_target_stays_red_and_independent_build_and_test_run(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "CMakeLists.txt").write_text("""cmake_minimum_required(VERSION 3.20)
project(Partial NONE)
enable_testing()
add_custom_target(broken ALL COMMAND ${CMAKE_COMMAND} -E false)
add_custom_target(healthy ALL COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/built)
add_test(NAME healthy COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/executed)
add_test(NAME unavailable COMMAND ${CMAKE_BINARY_DIR}/not-built)
""")
            generator = "Ninja" if shutil.which("ninja") else "Unix Makefiles"
            configure = subprocess.run(["cmake", "-S", ".", "-B", "build", "-G", generator], cwd=root, capture_output=True)
            self.assertEqual(configure.returncode, 0, configure.stderr)
            build = subprocess.run([sys.executable, str(SCRIPTS / "build_suite.py"), "--parallel", "1"], cwd=root, capture_output=True)
            self.assertNotEqual(build.returncode, 0)
            self.assertTrue((root / "build/built").exists(), build.stdout)
            (root / "source-lock.json").write_text(json.dumps(dict(test_regex=".*")))
            tests = subprocess.run([sys.executable, str(SCRIPTS / "run_suite.py"), "test"], cwd=root, capture_output=True)
            self.assertNotEqual(tests.returncode, 0)
            self.assertTrue((root / "build/executed").exists())
            cases = list(ET.parse(root / "build/results.xml").getroot().iter("testcase"))
            self.assertEqual(len(cases), 2)
            self.assertEqual(sum(any(c.find(tag) is not None for tag in ("failure", "error", "skipped")) for c in cases), 1)


if __name__ == "__main__":
    unittest.main()
