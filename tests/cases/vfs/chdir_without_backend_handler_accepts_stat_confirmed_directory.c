#include "support/vfs_operations_host.h"

int main(void)
{
    operation_fs.fchdir = NULL; prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_chdir("/store/dir") == 0);
    CHECK(stat_calls == 1 && chdir_calls == 0 && strcmp(operation_path, "/dir") == 0);
    vfs_stat_t st; CHECK(vfs_stat("file", &st) == 0);
    CHECK(strcmp(operation_path, "/dir/file") == 0); cleanup_operations();
    return EXIT_SUCCESS;
}
