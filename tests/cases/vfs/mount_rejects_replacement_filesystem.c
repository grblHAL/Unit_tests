#include "vfs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    vfs_t first = { .fs_name = "first" }, second = { .fs_name = "second" };
    CHECK(vfs_mount(NULL, "/test", &first, (vfs_st_mode_t){0}));
    CHECK(!vfs_mount(NULL, "/test", &second, (vfs_st_mode_t){0}));
    vfs_drive_t *drive = vfs_get_drive("/test");
    CHECK(drive && drive->fs == &first);
    CHECK(vfs_unmount(NULL, "/test"));
    return EXIT_SUCCESS;
}
