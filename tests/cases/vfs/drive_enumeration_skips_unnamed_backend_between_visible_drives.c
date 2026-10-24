#include "vfs.h"
#include "check.h"
#include <string.h>

int main(void)
{
    static const vfs_t first = {.fs_name = "first"};
    static const vfs_t unnamed = {0};
    static const vfs_t last = {.fs_name = "last", .removable = true};
    CHECK(vfs_mount(NULL, "/first", &first, (vfs_st_mode_t){.directory = true}));
    CHECK(vfs_mount(NULL, "/internal", &unnamed, (vfs_st_mode_t){.directory = true}));
    CHECK(vfs_mount(NULL, "/last", &last, (vfs_st_mode_t){.directory = true}));
    vfs_drives_t *handle = vfs_drives_open();
    CHECK(handle != NULL);
    vfs_drive_t *drive = vfs_drives_read(handle, false);
    CHECK(drive && drive->fs == &first && strcmp(drive->path, "/first/") == 0);
    drive = vfs_drives_read(handle, false);
    CHECK(drive && drive->fs == &last && strcmp(drive->name, "last") == 0);
    CHECK(drive->removable && strcmp(drive->path, "/last/") == 0);
    CHECK(vfs_drives_read(handle, false) == NULL);
    vfs_drives_close(handle);
    drive = vfs_get_drive("/internal/job.nc");
    CHECK(drive && drive->fs == &unnamed);
    CHECK(vfs_unmount(NULL, "/last"));
    CHECK(vfs_unmount(NULL, "/internal"));
    CHECK(vfs_unmount(NULL, "/first"));
    return EXIT_SUCCESS;
}
