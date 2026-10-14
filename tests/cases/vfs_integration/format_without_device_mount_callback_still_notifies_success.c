#include "support/vfs_drive_format_host.h"
int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    format_fs.device_mount = NULL;
    CHECK(vfs_drive_format(drive) == 0);
    CHECK(strcmp(format_events,"TUFM") == 0);
    CHECK(format_mount_calls == 0);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
