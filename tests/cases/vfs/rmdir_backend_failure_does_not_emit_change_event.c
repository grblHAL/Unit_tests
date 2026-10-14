#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0}); operation_result = -1;
    CHECK(vfs_rmdir("/store/dir") == -1);
    CHECK(rmdir_calls == 1 && change_calls == 0); cleanup_operations();
    return EXIT_SUCCESS;
}
