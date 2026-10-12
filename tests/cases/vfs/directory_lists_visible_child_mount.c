#include "support/vfs_directory_host.h"
#include "check.h"

int main(void)
{
    prepare_directory_root();
    vfs_t child = { .fs_name = "child" };
    CHECK(vfs_mount(NULL, "/child", &child, (vfs_st_mode_t){0}));
    vfs_dir_t *dir = vfs_opendir("/");
    CHECK(dir != NULL);
    vfs_dirent_t *entry = vfs_readdir(dir);
    CHECK(entry && strcmp(entry->name, "child") == 0 && entry->st_mode.directory);
    CHECK(vfs_readdir(dir) == NULL);
    vfs_closedir(dir);
    CHECK(directory_close_calls == 1);
    CHECK(vfs_unmount(NULL, "/child"));
    CHECK(vfs_unmount(NULL, "/"));
    return EXIT_SUCCESS;
}
