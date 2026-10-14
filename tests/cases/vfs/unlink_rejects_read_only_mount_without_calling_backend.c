#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){.read_only = true});
    CHECK(vfs_unlink("/store/program.nc") == -1);
    CHECK(vfs_errno == EROFS && unlink_calls == 0 && change_calls == 0);
    cleanup_operations();
    return EXIT_SUCCESS;
}
