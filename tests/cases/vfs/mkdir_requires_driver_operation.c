#include "vfs.h"
#include <errno.h>
#include <string.h>
#include "check.h"

int main(void)
{
    vfs_t fs = { .fs_name = "test" };
    CHECK(vfs_mount(NULL, "/test", &fs, (vfs_st_mode_t){0}));
    CHECK(vfs_mkdir("/test/new") == -1);
    CHECK(vfs_errno == EPERM);
    CHECK(vfs_unmount(NULL, "/test"));
    return EXIT_SUCCESS;
}
