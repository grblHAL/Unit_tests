"""Forwarding headers must track CORE changes without rebuilding unchanged cases."""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class ComponentHeaderTests(unittest.TestCase):
    def test_reconfigure_preserves_headers_and_core_switch_updates_them(self):
        with tempfile.TemporaryDirectory(prefix="component-headers-") as directory:
            root = Path(directory)
            project, build = root / "project", root / "build"
            first, second = root / "first core", root / "second core"
            for folder in (project, first, second):
                folder.mkdir()
            # Header generation only: no firmware source or compiler is substituted.
            for core in (first, second):
                (core / "hal.h").write_text("#pragma once\n")
            helper = (ROOT / "tests/components.cmake").as_posix()
            (project / "CMakeLists.txt").write_text(
                'cmake_minimum_required(VERSION 3.20)\n'
                'project(component_headers NONE)\n'
                f'include("{helper}")\n'
            )

            def configure(core):
                subprocess.run(
                    ["cmake", "-S", str(project), "-B", str(build),
                     "-DCOMPONENT_CORE_ROOT=" + core.as_posix()],
                    check=True, capture_output=True, text=True,
                )

            header = build / "include/grbl/hal.h"
            configure(first)
            first_content = f'#include "{(first / "hal.h").as_posix()}"\n'
            self.assertEqual(header.read_text(), first_content)
            timestamp = header.stat().st_mtime_ns
            configure(first)
            self.assertEqual(header.stat().st_mtime_ns, timestamp)
            configure(second)
            self.assertEqual(header.read_text(), f'#include "{(second / "hal.h").as_posix()}"\n')
            timestamp = header.stat().st_mtime_ns
            configure(second)
            self.assertEqual(header.stat().st_mtime_ns, timestamp)
            configure(first)
            self.assertEqual(header.read_text(), first_content)


if __name__ == "__main__":
    unittest.main()
