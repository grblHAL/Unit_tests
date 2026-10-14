#include "support/vfs_drive_format_host.h"
int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    drive_space_ok = false;
    CHECK(vfs_drive_getfree(drive) == NULL);
    CHECK(drive_space_calls == 1);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
