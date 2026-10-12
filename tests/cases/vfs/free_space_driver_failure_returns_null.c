#include "vfs.h"
#include "check.h"
static bool get_free(vfs_free_t *space) { (void)space; return false; }
int main(void)
{
    vfs_t fs = { .fs_name = "test", .fgetfree = get_free };
    CHECK(vfs_mount(NULL, "/test", &fs, (vfs_st_mode_t){0}));
    CHECK(vfs_fgetfree("/test/file") == NULL);
    CHECK(vfs_unmount(NULL, "/test"));
    return EXIT_SUCCESS;
}
