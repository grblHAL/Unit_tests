#include "support/vfs_drive_format_host.h"
int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    format_fs.format = NULL;
    CHECK(vfs_drive_format(drive) == -1);
    CHECK(strcmp(format_events,"T") == 0);
    CHECK(format_calls == 0 && format_mount_calls == 0);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
