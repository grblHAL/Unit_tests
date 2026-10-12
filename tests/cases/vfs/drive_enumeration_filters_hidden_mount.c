#include "vfs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    vfs_t visible = { .fs_name = "visible", .removable = true }, hidden = { .fs_name = "hidden" };
    CHECK(vfs_mount(NULL, "/visible", &visible, (vfs_st_mode_t){0}));
    CHECK(vfs_mount(NULL, "/hidden", &hidden, (vfs_st_mode_t){ .hidden = true }));
    vfs_drives_t *handle = vfs_drives_open();
    CHECK(handle != NULL);
    vfs_drive_t *drive = vfs_drives_read(handle, false);
    CHECK(drive && strcmp(drive->name, "visible") == 0 && drive->removable);
    CHECK(vfs_drives_read(handle, false) == NULL);
    vfs_drives_close(handle);
    CHECK(vfs_unmount(NULL, "/visible"));
    CHECK(vfs_unmount(NULL, "/hidden"));
    return EXIT_SUCCESS;
}
