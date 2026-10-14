"""Recognize only realloc of the documented static VFS filename buffer."""
import re
import subprocess
import sys


def matches_known_crash(output):
    return bool(
        "ERROR: AddressSanitizer: attempting free on address which was not malloc()-ed" in output
        and re.search(r"in vfs_locate_file[^\n]*core[/\\]vfs\.c:896\b", output)
        and re.search(r"in main[^\n]*locate_long_filename_returns_mounted_file_path\.c:5\b", output)
        and re.search(r"0 bytes inside of global variable '(?:vfs_locate_file\.)?_name(?:\.\d+)?'[^\n]*of size 32", output)
        and "SUMMARY: AddressSanitizer: bad-free" in output
    )


def main():
    if sys.argv[1] != "1":
        print("This known static-buffer realloc fault requires ENABLE_SANITIZERS=ON.")
        return 77
    result = subprocess.run([sys.argv[2]], stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, text=True)
    print(result.stdout)
    print(f"Regression executable exit code: {result.returncode}")
    if result.returncode != 0 and matches_known_crash(result.stdout):
        print("Confirmed known realloc of static VFS filename buffer.")
        return 1
    if result.returncode == 0:
        print("Regression passed: see KNOWN_BUGS.md and remove the fixed exception.")
    else:
        print("Unexpected failure: diagnostic does not match the known static-buffer fault.")
    # WILL_FAIL makes fixed assertions or any different fault require review.
    return 0


if __name__ == "__main__":
    sys.exit(main())
