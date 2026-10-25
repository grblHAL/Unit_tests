import json
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

from check_arm_modules import STM32, check, is_arm_object, module_plan


def arm_object():
    data = bytearray(52)
    data[:6] = b"\x7fELF\x01\x01"
    data[16:18] = (1).to_bytes(2, "little")
    data[18:20] = (40).to_bytes(2, "little")
    return bytes(data)


class ArmModulesTests(unittest.TestCase):
    def test_plans_use_original_serial_and_full_sdk_units(self):
        checks = 0
        for family in [*STM32, "lpc176x"]:
            for mcu, flags, includes, modules in module_plan(family):
                with self.subTest(mcu=mcu):
                    self.assertIn("-mthumb", flags)
                    self.assertTrue(any(flag.startswith("-mcpu=cortex-m") for flag in flags))
                    self.assertTrue(modules[0].endswith("/serial.c"))
                    self.assertTrue(all(module.endswith(".c") for module in modules))
                    self.assertTrue(any("uart" in module.lower() for module in modules[1:]))
                    self.assertGreaterEqual(len(includes), 2)
                    checks += len(modules)
        self.assertEqual(checks, 15)

    def test_architecture_check_rejects_native_or_executable_output(self):
        self.assertTrue(is_arm_object(arm_object()))
        for offset, value in [(4, 2), (5, 2), (16, 2), (18, 62)]:
            data = bytearray(arm_object())
            data[offset] = value
            self.assertFalse(is_arm_object(data))
        self.assertFalse(is_arm_object(b""))

    def test_failed_module_does_not_stop_other_modules_or_accept_stale_object(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary).resolve()
            driver = root / "drivers/stm32h7"
            (root / "core").mkdir()
            (root / "core/hal.h").write_text("/* original header */\n")
            for _, _, _, modules in module_plan("stm32h7"):
                for module in modules:
                    source = driver / module
                    source.parent.mkdir(parents=True, exist_ok=True)
                    source.write_text("/* unchanged original source */\n")
            lock = {"path": "drivers/stm32h7", "sources": [
                {"path": "drivers/stm32h7", "sha": "a" * 40},
                {"path": "core", "sha": "b" * 40}]}
            calls = []

            def compile_module(command, **kwargs):
                calls.append(command)
                Path(command[-1]).write_bytes(arm_object())
                return subprocess.CompletedProcess(command, int(len(calls) == 1), "", "warning: SDK\n")

            with patch("check_arm_modules.prepare") as prepare, \
                    patch("check_arm_modules.subprocess.check_output", return_value="ARM compiler\n"), \
                    patch("check_arm_modules.subprocess.run", side_effect=compile_module):
                self.assertEqual(check(root, lock, root / "objects", "gcc"), 1)
                self.assertEqual(prepare.call_count, 2)
            results = json.loads((root / "objects/results.json").read_text())
            self.assertEqual(len(calls), 4)
            self.assertEqual([item["passed"] for item in results["checks"]], [False, True, True, True])
            self.assertIsNone(results["checks"][0]["object_sha256"])
            self.assertEqual(results["source_lock"], lock)
            self.assertTrue(all(not item["runtime_executed"] for item in results["checks"]))
            self.assertEqual((root / "core/hal.h").read_text(), "/* original header */\n")


if __name__ == "__main__":
    unittest.main()
