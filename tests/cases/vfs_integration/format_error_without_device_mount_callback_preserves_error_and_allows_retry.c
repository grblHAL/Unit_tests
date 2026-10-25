#include "support/vfs_drive_format_host.h"

int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    CHECK(drive != NULL);
    format_fs.device_mount = NULL;
    format_result = -7;
    CHECK(vfs_drive_format(drive) == -7 && vfs_errno == -7);
    CHECK(strcmp(format_events, "TUF") == 0);
    CHECK(format_calls == 1 && format_mount_calls == 0);
    vfs_drive_t *still_mounted = vfs_get_drive("/store/next.nc");
    CHECK(still_mounted != NULL && still_mounted->fs == &format_fs);
    format_events[0] = 0;
    format_result = 0;
    CHECK(vfs_drive_format(drive) == 0 && vfs_errno == 0);
    CHECK(strcmp(format_events, "TUFM") == 0);
    CHECK(format_calls == 2 && format_mount_calls == 0);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
