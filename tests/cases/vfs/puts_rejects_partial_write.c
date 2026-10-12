#include "vfs.h"
#include <errno.h>
#include <string.h>
#include "check.h"
static size_t partial_write(const void *buffer, size_t size, size_t count, vfs_file_t *file) { (void)buffer; (void)size; (void)file; vfs_errno = ENOSPC; return count - 1; }
int main(void)
{
    vfs_t fs = { .fwrite = partial_write };
    vfs_file_t file = { .fs = &fs };
    CHECK(vfs_puts("hello", &file) == -1);
    CHECK(vfs_errno == ENOSPC);
    return EXIT_SUCCESS;
}
