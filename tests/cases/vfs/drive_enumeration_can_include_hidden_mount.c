#include "vfs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    vfs_t visible = { .fs_name = "visible" }, hidden = { .fs_name = "hidden" };
    CHECK(vfs_mount(NULL, "/visible", &visible, (vfs_st_mode_t){0}));
    CHECK(vfs_mount(NULL, "/hidden", &hidden, (vfs_st_mode_t){ .hidden = true }));
    vfs_drives_t *handle = vfs_drives_open();
    CHECK(handle != NULL);
    CHECK(vfs_drives_read(handle, true) != NULL);
    vfs_drive_t *drive = vfs_drives_read(handle, true);
    CHECK(drive && strcmp(drive->name, "hidden") == 0 && drive->mode.hidden);
    CHECK(vfs_drives_read(handle, true) == NULL);
    vfs_drives_close(handle);
    CHECK(vfs_unmount(NULL, "/visible"));
    CHECK(vfs_unmount(NULL, "/hidden"));
    return EXIT_SUCCESS;
}
