#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0}); CHECK(vfs_chdir("/store/dir") == 0);
    vfs_stat_t st;
    CHECK(vfs_stat(".././file", &st) == 0);
    CHECK(strcmp(operation_path, "/file") == 0 && st.st_size == 123);
    cleanup_operations();
    return EXIT_SUCCESS;
}
