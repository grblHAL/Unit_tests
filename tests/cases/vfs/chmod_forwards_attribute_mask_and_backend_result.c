#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0}); operation_result = -7;
    vfs_st_mode_t attr = {.read_only = true}, mask = {.read_only = true, .archive = true};
    CHECK(vfs_chmod("/store/file", attr, mask) == -7);
    CHECK(strcmp(operation_path, "/file") == 0);
    CHECK(chmod_attr.mode == attr.mode && chmod_mask.mode == mask.mode); cleanup_operations();
    return EXIT_SUCCESS;
}
