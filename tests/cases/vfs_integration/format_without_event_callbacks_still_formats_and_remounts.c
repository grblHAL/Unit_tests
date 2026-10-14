#include "support/vfs_drive_format_host.h"
int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    vfs.on_unmount = NULL;
    vfs.on_mount = NULL;
    CHECK(vfs_drive_format(drive) == 0);
    CHECK(strcmp(format_events,"TFR") == 0);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
