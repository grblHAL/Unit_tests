#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_mkdir("/store/jobs/../new") == 0);
    CHECK(strcmp(operation_path, "/new") == 0 && mkdir_calls == 1 && change_calls == 1);
    cleanup_operations();
    return EXIT_SUCCESS;
}
