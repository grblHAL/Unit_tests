#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){.hidden = true});
    CHECK(vfs_unlink("/store/program.nc") == -1);
    CHECK(vfs_errno == EFAULT && unlink_calls == 0 && change_calls == 0);
    cleanup_operations();
    return EXIT_SUCCESS;
}
