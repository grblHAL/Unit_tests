#include "vfs.h"
#include "check.h"
#include <string.h>

int main(void)
{
    const vfs_t *backend = vfs_get_drive("/")->fs;
    vfs_t child = {.fs_name = "fixture"};
    CHECK(vfs_mount(NULL, "/fixture", &child, (vfs_st_mode_t){.read_only = true}));
    vfs_stat_t st = {0};
    CHECK(backend->fstat("fixture", &st) == 0);
    CHECK(st.st_mode.directory && st.st_mode.read_only && !st.st_mode.hidden);
    CHECK(vfs_unmount(NULL, "/fixture"));
    return EXIT_SUCCESS;
}
