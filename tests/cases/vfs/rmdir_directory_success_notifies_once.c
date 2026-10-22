#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_rmdir("/store/dir") == 0);
    CHECK(stat_calls == 1 && rmdir_calls == 1 && change_calls == 1);
    CHECK(strcmp(operation_path, "/dir") == 0);
    vfs.on_fs_changed = NULL;
    CHECK(vfs_rmdir("/store/other") == 0);
    CHECK(stat_calls == 2 && rmdir_calls == 2 && change_calls == 1);
    CHECK(strcmp(operation_path, "/other") == 0);
    cleanup_operations();
    return EXIT_SUCCESS;
}
