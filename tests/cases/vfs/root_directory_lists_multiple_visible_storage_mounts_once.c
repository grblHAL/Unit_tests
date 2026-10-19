#include "support/vfs_storage_mounts_host.h"
int main(void)
{
    mount_storage_directories();
    vfs_dir_t *dir = vfs_opendir("/");
    CHECK(dir != NULL);
    check_visible_storage_directories(dir);
    vfs_closedir(dir);
    unmount_storage_directories();
    return EXIT_SUCCESS;
}
