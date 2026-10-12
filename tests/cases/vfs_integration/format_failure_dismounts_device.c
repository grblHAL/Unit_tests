#include "support/vfs_format_host.h"
#include "check.h"

int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    format_result = 5;
    CHECK(vfs_drive_format(drive) == 5 && vfs_errno == 5);
    CHECK(format_calls == 1 && unmount_calls == 1 && mount_calls == 0);
    CHECK(device_mount_calls == 0 && device_unmount_calls == 1);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
