#include "vfs.h"
#include <errno.h>
#include <string.h>
#include "check.h"
static size_t captured_size, captured_count;
static char captured_text[16];
static size_t write_file(const void *buffer, size_t size, size_t count, vfs_file_t *file) { (void)file; captured_size = size; captured_count = count; memcpy(captured_text, buffer, size * count); return count; }
int main(void)
{
    vfs_t fs = { .fwrite = write_file };
    vfs_file_t file = { .fs = &fs };
    vfs_errno = EIO;
    CHECK(vfs_puts("hello", &file) == 5);
    CHECK(captured_size == 1 && captured_count == 5);
    CHECK(memcmp(captured_text, "hello", 5) == 0);
    CHECK(vfs_errno == 0);
    return EXIT_SUCCESS;
}
