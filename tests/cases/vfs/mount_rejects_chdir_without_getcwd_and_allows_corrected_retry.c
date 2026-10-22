#include "support/vfs_operations_host.h"
#include "check.h"

int main(void)
{
    operation_fs.fgetcwd = NULL;
    CHECK(!vfs_mount(NULL, "/store", &operation_fs, (vfs_st_mode_t){0}));
    CHECK(chdir_calls == 0);
    operation_fs.fgetcwd = operation_getcwd;
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_chdir("/store/dir") == 0);
    CHECK(vfs_chdir("/store/other") == 0);
    CHECK(vfs_unlink("file") == 0);
    CHECK(strcmp(operation_path, "/other/file") == 0);
    CHECK(strcmp(unlink_directory, "/other") == 0);
    cleanup_operations();
    return EXIT_SUCCESS;
}
