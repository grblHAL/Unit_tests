#include "vfs.h"
#include <string.h>
#include "check.h"
static unsigned unmount_calls;
static void unmounted(const char *path) { CHECK(strcmp(path, "/test") == 0); unmount_calls++; }
int main(void)
{
    vfs_t fs = { .fs_name = "test" };
    CHECK(vfs_mount(NULL, "/test", &fs, (vfs_st_mode_t){0}));
    vfs.on_unmount = unmounted;
    CHECK(vfs_unmount(NULL, "/test"));
    CHECK(unmount_calls == 1);
    return EXIT_SUCCESS;
}
