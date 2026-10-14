#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_chdir("/store/dir") == 0); operation_result = -1;
    CHECK(vfs_chdir("/store/other") == -1); operation_result = 0;
    CHECK(vfs_unlink("file") == 0);
    CHECK(strcmp(operation_path, "file") == 0 && strcmp(unlink_directory, "/dir") == 0); cleanup_operations();
    return EXIT_SUCCESS;
}
