#include "support/vfs_resource_host.h"
int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    vfs_t other = operation_fs; other.fs_name = "second";
    reject_calloc = 1;
    /* A separate regression checks the failed call's return/event contract. */
    (void)vfs_mount(NULL, "/second", &other, (vfs_st_mode_t){0});
    CHECK(calloc_failures == 1 && strcmp(vfs_get_drive("/second")->path, "/") == 0);
    CHECK(vfs_mount(NULL, "/second", &other, (vfs_st_mode_t){0}));
    vfs_drives_t *drives = vfs_drives_open(); CHECK(drives);
    unsigned count = 0; vfs_drive_t *drive;
    while((drive = vfs_drives_read(drives, false))) { CHECK(++count <= 2); }
    CHECK(count == 2); vfs_drives_close(drives);
    CHECK(vfs_unmount(NULL, "/second")); cleanup_operations();
    return EXIT_SUCCESS;
}
