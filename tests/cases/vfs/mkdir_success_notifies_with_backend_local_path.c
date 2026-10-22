#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_mkdir("/store/jobs/../new") == 0);
    CHECK(strcmp(operation_path, "/new") == 0 && mkdir_calls == 1 && change_calls == 1);
    operation_result = -1;
    CHECK(vfs_mkdir("/store/retry") == -1);
    CHECK(mkdir_calls == 2 && change_calls == 1);
    operation_result = 0;
    CHECK(vfs_mkdir("/store/retry") == 0);
    CHECK(mkdir_calls == 3 && change_calls == 2);
    vfs.on_fs_changed = NULL;
    CHECK(vfs_mkdir("/store/without-observer") == 0);
    CHECK(mkdir_calls == 4 && change_calls == 2);
    CHECK(strcmp(operation_path, "/without-observer") == 0);
    cleanup_operations();
    return EXIT_SUCCESS;
}
