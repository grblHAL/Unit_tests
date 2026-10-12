#include "support/vfs_format_host.h"
#include "check.h"

int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    format_fs.format = NULL;
    CHECK(vfs_drive_format(drive) == -1);
    CHECK(format_calls == 0 && unmount_calls == 0 && mount_calls == 0);
    CHECK(device_mount_calls == 0 && device_unmount_calls == 0);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
