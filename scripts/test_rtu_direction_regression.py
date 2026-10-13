import unittest
from rtu_direction_regression import matches_known_crash

WINDOWS = """ERROR: AddressSanitizer: access-violation on unknown address 0xfffffffffffffff8
#0 0x123 in modbus_rtu_init C:/checkout/core/modbus_rtu.c:601:27
#2 0x456 in main C:/checkout/tests/cases/modbus_rtu/aux_direction_without_outputs_disables_transport_safely.c:5:12
"""
LINUX = """ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000
#0 0x0 (<unknown module>)
#1 0x123 in modbus_rtu_init /checkout/core/modbus_rtu.c:601
#3 0x456 in main /checkout/tests/cases/modbus_rtu/aux_direction_without_outputs_disables_transport_safely.c:5
"""


class DirectionCrashMatcherTests(unittest.TestCase):
    def test_windows_access_violation(self):
        self.assertTrue(matches_known_crash(WINDOWS))

    def test_linux_null_call(self):
        self.assertTrue(matches_known_crash(LINUX))

    def test_other_source_line_rejected(self):
        self.assertFalse(matches_known_crash(WINDOWS.replace("c:601", "c:602")))

    def test_other_fault_address_rejected(self):
        self.assertFalse(matches_known_crash(WINDOWS.replace("0xfffffffffffffff8", "0x1234")))

    def test_other_executable_rejected(self):
        self.assertFalse(matches_known_crash(WINDOWS.replace("aux_direction_without_outputs_disables_transport_safely", "unrelated")))

    def test_heap_fault_rejected(self):
        self.assertFalse(matches_known_crash(WINDOWS.replace("access-violation", "heap-use-after-free")))

    def test_missing_asan_error_rejected(self):
        self.assertFalse(matches_known_crash(WINDOWS.split("\n", 1)[1]))


if __name__ == "__main__":
    unittest.main()
