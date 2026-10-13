#include "vfs.h"
#include "check.h"
#include <string.h>

int main(void)
{
    vfs_t child = {.fs_name = "fixture"};
    CHECK(vfs_mount(NULL, "/fixture", &child, (vfs_st_mode_t){0}));
    vfs_dir_t *dir = vfs_opendir("/");
    CHECK(dir != NULL);
    vfs_dirent_t *entry = vfs_readdir(dir);
    CHECK(entry != NULL);
    CHECK(strcmp(entry->name, "fixture") == 0 && entry->st_mode.directory);
    CHECK(vfs_readdir(dir) == NULL);
    vfs_closedir(dir);
    CHECK(vfs_unmount(NULL, "/fixture"));
    return EXIT_SUCCESS;
}
