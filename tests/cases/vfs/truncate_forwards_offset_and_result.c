#include "vfs.h"
#include <errno.h>
#include "check.h"
static vfs_file_t *captured_file;
static size_t captured_offset;
static int truncate_file(vfs_file_t *file, size_t offset) { captured_file = file; captured_offset = offset; return 7; }
int main(void)
{
    vfs_t fs = { .ftruncate = truncate_file };
    vfs_file_t file = { .fs = &fs };
    vfs_errno = EIO;
    CHECK(vfs_truncate(&file, 37) == 7);
    CHECK(captured_file == &file && captured_offset == 37);
    CHECK(vfs_errno == 0);
    return EXIT_SUCCESS;
}
