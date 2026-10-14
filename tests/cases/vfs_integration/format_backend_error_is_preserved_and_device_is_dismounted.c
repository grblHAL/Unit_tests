#include "support/vfs_drive_format_host.h"
int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    format_result = -7;
    CHECK(vfs_drive_format(drive) == -7);
    CHECK(vfs_errno == -7);
    CHECK(strcmp(format_events,"TUFD") == 0);
    CHECK(format_mount_calls == 1);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
