#include "support/vfs_drive_format_host.h"
int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    CHECK(vfs_drive_format(drive) == 0);
    CHECK(strcmp(format_events,"TUFRM") == 0);
    CHECK(format_calls == 1 && format_mount_calls == 1 && format_drain_calls == 1);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
