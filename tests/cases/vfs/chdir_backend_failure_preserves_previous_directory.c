#include "support/vfs_operations_host.h"

static bool reject_next_change;
static int change_directory(const char *path)
{
    if(reject_next_change) {
        reject_next_change = false;
        return -1;
    }
    return operation_chdir(path);
}

int main(void)
{
    operation_fs.fchdir = change_directory;
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_chdir("/store/dir") == 0); reject_next_change = true;
    CHECK(vfs_chdir("/store/other") == -1);
    CHECK(vfs_errno == EAGAIN);
    CHECK(vfs_unlink("file") == 0);
    CHECK(strcmp(operation_path, "/dir/file") == 0 && strcmp(unlink_directory, "/dir") == 0); cleanup_operations();
    return EXIT_SUCCESS;
}
