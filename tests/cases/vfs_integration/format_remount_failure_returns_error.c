#include "support/vfs_format_host.h"
#include "check.h"

int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    allow_remount = false;
    CHECK(vfs_drive_format(drive) == -1);
    CHECK(format_calls == 1 && unmount_calls == 1 && mount_calls == 0);
    CHECK(device_mount_calls == 1 && device_unmount_calls == 1);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
