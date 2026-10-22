#include "support/vfs_resource_host.h"
#include "support/vfs_storage_mounts_host.h"

int main(void)
{
    mount_storage_directories();
    reject_calloc = 1;
    CHECK(vfs_opendir("/") == NULL);
    CHECK(calloc_failures == 1);
    vfs_dir_t *dir = vfs_opendir("/");
    CHECK(dir != NULL);
    check_visible_storage_directories(dir);
    vfs_closedir(dir);
    dir = vfs_opendir("/");
    CHECK(dir != NULL);
    check_visible_storage_directories(dir);
    vfs_closedir(dir);
    CHECK(calloc_failures == 1 && malloc_failures == 0 && realloc_failures == 0);
    unmount_storage_directories();
    return EXIT_SUCCESS;
}
