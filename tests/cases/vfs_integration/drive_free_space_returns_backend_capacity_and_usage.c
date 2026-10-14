#include "support/vfs_drive_format_host.h"
int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    vfs_free_t *space = vfs_drive_getfree(drive);
    CHECK(space && space->size == 8192 && space->used == 512);
    CHECK(drive_space_calls == 1);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
