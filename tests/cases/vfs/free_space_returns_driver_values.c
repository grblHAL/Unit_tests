#include "vfs.h"
#include "check.h"
static bool get_free(vfs_free_t *space) { space->size = 4096; space->used = 1024; return true; }
int main(void)
{
    vfs_t fs = { .fs_name = "test", .fgetfree = get_free };
    CHECK(vfs_mount(NULL, "/test", &fs, (vfs_st_mode_t){0}));
    vfs_free_t *space = vfs_fgetfree("/test/file");
    CHECK(space && space->size == 4096 && space->used == 1024);
    CHECK(vfs_unmount(NULL, "/test"));
    return EXIT_SUCCESS;
}
