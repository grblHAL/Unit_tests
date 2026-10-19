#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_chdir("/store/jobs") == 0);
    CHECK(vfs_unlink("../program.nc") == 0);
    CHECK(strcmp(operation_path, "/program.nc") == 0 && strcmp(unlink_directory, "/jobs") == 0);
    CHECK(unlink_calls == 1 && change_calls == 1); cleanup_operations();
    return EXIT_SUCCESS;
}
