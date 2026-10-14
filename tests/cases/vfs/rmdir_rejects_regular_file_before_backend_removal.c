#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0}); stat_directory = false;
    CHECK(vfs_rmdir("/store/file") == -1);
    CHECK(vfs_errno == ENOTDIR && stat_calls == 1 && rmdir_calls == 0 && change_calls == 0);
    cleanup_operations();
    return EXIT_SUCCESS;
}
