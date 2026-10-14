#include "support/vfs_drive_format_host.h"
int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    format_remount_ok = false;
    CHECK(vfs_drive_format(drive) == -1);
    CHECK(strcmp(format_events,"TUFRD") == 0);
    CHECK(format_mount_calls == 2);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
