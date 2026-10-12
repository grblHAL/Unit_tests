#include "vfs.h"
#include <errno.h>
#include "check.h"

int main(void)
{
    vfs_t fs = {0};
    vfs_file_t file = { .fs = &fs };
    CHECK(vfs_truncate(&file, 12) == -1);
    CHECK(vfs_errno == EPERM);
    return EXIT_SUCCESS;
}
