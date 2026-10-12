#include "vfs.h"
#include <errno.h>
#include "check.h"
static vfs_file_t *captured_file;
static size_t captured_offset;
static int seek_file(vfs_file_t *file, size_t offset) { captured_file = file; captured_offset = offset; vfs_errno = EINVAL; return -1; }
int main(void)
{
    vfs_t fs = { .fseek = seek_file };
    vfs_file_t file = { .fs = &fs };
    vfs_errno = EIO;
    CHECK(vfs_seek(&file, 123) == -1);
    CHECK(captured_file == &file && captured_offset == 123);
    CHECK(vfs_errno == EINVAL);
    return EXIT_SUCCESS;
}
