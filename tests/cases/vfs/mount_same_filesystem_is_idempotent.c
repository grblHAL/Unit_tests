#include "vfs.h"
#include <string.h>
#include "check.h"
static unsigned mount_calls;
static void mounted(const char *path, const vfs_t *fs, vfs_st_mode_t mode) { (void)fs; (void)mode; CHECK(strcmp(path, "/test") == 0); mount_calls++; }
int main(void)
{
    vfs_t fs = { .fs_name = "test" };
    vfs.on_mount = mounted;
    CHECK(vfs_mount(NULL, "/test", &fs, (vfs_st_mode_t){0}));
    CHECK(vfs_mount(NULL, "/test", &fs, (vfs_st_mode_t){0}));
    CHECK(mount_calls == 1);
    CHECK(vfs_unmount(NULL, "/test"));
    return EXIT_SUCCESS;
}
