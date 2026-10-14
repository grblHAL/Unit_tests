import unittest
from vfs_path_regression import matches_known_crash

WINDOWS = """ERROR: AddressSanitizer: attempting free on address which was not malloc()-ed: 0x123
#1 0x123 in vfs_locate_file C:/checkout/core/vfs.c:896:69
#2 0x456 in main C:/checkout/tests/cases/vfs/locate_long_filename_returns_mounted_file_path.c:5:24
0x123 is located 0 bytes inside of global variable 'vfs_locate_file._name' defined in 'C:/checkout/core/vfs.c' of size 32
SUMMARY: AddressSanitizer: bad-free C:/checkout/core/vfs.c:896:69
"""
LINUX = WINDOWS.replace('vfs_locate_file._name', '_name').replace('C:/checkout', '/checkout')


class StaticFilenameMatcherTests(unittest.TestCase):
    def test_captured_windows_shape(self):
        self.assertTrue(matches_known_crash(WINDOWS))

    def test_linux_global_name_shape(self):
        self.assertTrue(matches_known_crash(LINUX))

    def test_other_core_line_rejected(self):
        self.assertFalse(matches_known_crash(WINDOWS.replace('c:896', 'c:897')))

    def test_other_case_rejected(self):
        self.assertFalse(matches_known_crash(WINDOWS.replace('locate_long_filename_returns_mounted_file_path.c', 'unrelated.c')))

    def test_other_global_rejected(self):
        self.assertFalse(matches_known_crash(WINDOWS.replace('vfs_locate_file._name', 'unrelated')))

    def test_other_global_size_rejected(self):
        self.assertFalse(matches_known_crash(WINDOWS.replace('of size 32', 'of size 64')))

    def test_other_fault_rejected(self):
        self.assertFalse(matches_known_crash(WINDOWS.replace('bad-free', 'heap-use-after-free')))

    def test_missing_asan_error_rejected(self):
        self.assertFalse(matches_known_crash(WINDOWS.split('\n', 1)[1]))


if __name__ == '__main__':
    unittest.main()
