#include "vfs.h"
#include "check.h"

int main(void)
{
    vfs_t fs = { .fs_name = "test" };
    CHECK(vfs_mount(NULL, "/test", &fs, (vfs_st_mode_t){0}));
    CHECK(vfs_chmod("/test/file", (vfs_st_mode_t){ .read_only = true }, (vfs_st_mode_t){ .read_only = true }) == -1);
    CHECK(vfs_unmount(NULL, "/test"));
    return EXIT_SUCCESS;
}
