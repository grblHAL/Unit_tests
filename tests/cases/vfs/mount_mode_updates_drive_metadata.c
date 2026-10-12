#include "vfs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    vfs_t fs = { .fs_name = "test" };
    CHECK(vfs_mount(NULL, "/test", &fs, (vfs_st_mode_t){0}));
    CHECK(vfs_mount_set_mode("/test", (vfs_st_mode_t){ .read_only = true, .hidden = true }));
    vfs_drive_t *drive = vfs_get_drive("/test");
    CHECK(drive && drive->mode.read_only && drive->mode.hidden);
    CHECK(vfs_unmount(NULL, "/test"));
    return EXIT_SUCCESS;
}
