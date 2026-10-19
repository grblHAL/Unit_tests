#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_unlink("/store/a/.././program.nc") == 0);
    CHECK(strcmp(operation_path, "/program.nc") == 0);
    CHECK(unlink_calls == 1 && change_calls == 1); cleanup_operations();
    return EXIT_SUCCESS;
}
