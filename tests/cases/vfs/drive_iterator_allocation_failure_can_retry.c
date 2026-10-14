#include "support/vfs_resource_host.h"
int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    rejected_size = sizeof(vfs_drives_t); reject_malloc = 1;
    CHECK(vfs_drives_open() == NULL && malloc_failures == 1);
    vfs_drives_t *drives = vfs_drives_open(); CHECK(drives);
    vfs_drive_t *drive = vfs_drives_read(drives, false);
    CHECK(drive && drive->fs == &operation_fs && strcmp(drive->path, "/store/") == 0);
    CHECK(vfs_drives_read(drives, false) == NULL);
    vfs_drives_close(drives); cleanup_operations();
    return EXIT_SUCCESS;
}
