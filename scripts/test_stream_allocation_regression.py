import unittest
from stream_allocation_regression import matches_known_crash

WINDOWS = """Injected auxiliary stream allocation failure
/checkout/core/stream.c:310:17: runtime error: member access within null pointer of type 'stream_connection_t' (aka 'struct stream_connection')
ERROR: AddressSanitizer: access-violation on unknown address 0x000000000008
The signal is caused by a WRITE memory access.
#0 in add_connection /checkout/core/stream.c
#2 in stream_connect /checkout/core/stream.c:489:24
#3 in main /checkout/tests/cases/stream/auxiliary_connection_allocation_failure_preserves_primary_stream.c:7:12
SUMMARY: AddressSanitizer: access-violation /checkout/core/stream.c in add_connection
"""
LINUX = WINDOWS.replace('access-violation','SEGV').replace("'stream_connection_t' (aka 'struct stream_connection')", "'struct stream_connection'")

class StreamAllocationMatcherTests(unittest.TestCase):
    def test_captured_windows_diagnostic(self):
        self.assertTrue(matches_known_crash(WINDOWS))

    def test_linux_diagnostic_shape(self):
        self.assertTrue(matches_known_crash(LINUX))

    def test_missing_sanitizer_summary_is_rejected(self):
        self.assertFalse(matches_known_crash(WINDOWS.split("SUMMARY:")[0]))

    def test_plain_assertion_failure_is_rejected(self):
        self.assertFalse(matches_known_crash("Injected auxiliary stream allocation failure\nCHECK failed: primary stream preserved"))

    def test_unrelated_faults_are_rejected(self):
        for original,replacement in [('stream.c:310','stream.c:311'), ('stream.c:489','stream.c:490'),
            ('0x000000000008','0x000000000010'), ('WRITE memory access','READ memory access'),
            ('in add_connection','in unrelated_function'), ('stream_connection_t','other_type'),
            ('preserves_primary_stream.c:7','preserves_primary_stream.c:8'),
            ('Injected auxiliary stream allocation failure','No allocation failure injected')]:
            with self.subTest(replacement=replacement):
                self.assertFalse(matches_known_crash(WINDOWS.replace(original,replacement)))

if __name__ == '__main__':
    unittest.main()
