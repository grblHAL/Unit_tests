#include "support/device_filesystem_host.h"

int main(void)
{
    prepare_device_filesystem();
    CHECK(vfs_mount_set_mode("/dev", (vfs_st_mode_t){.directory = true}));
    CHECK(vfs_unlink("/dev/uart2") == -1);
    CHECK(vfs_mkdir("/dev/subdir") == -1);
    CHECK(vfs_rmdir("/dev/subdir") == -1);
    CHECK(vfs_chdir("/dev/subdir") == -1);
    CHECK(vfs_opendir("/dev") == NULL);
    vfs_file_t *file = vfs_open("/dev/uart2", "w");
    CHECK(file != NULL);
    backend_close(file);
    return EXIT_SUCCESS;
}
