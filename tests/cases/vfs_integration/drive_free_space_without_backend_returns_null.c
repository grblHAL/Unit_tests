#include "support/vfs_drive_format_host.h"
int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    format_fs.fgetfree = NULL;
    CHECK(vfs_drive_getfree(drive) == NULL);
    CHECK(drive_space_calls == 0);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
