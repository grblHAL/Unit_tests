#include "support/vfs_operations_host.h"
int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    char path[128] = "/store/"; memset(path + 7, 'a', 110); path[117] = 0;
    CHECK(vfs_chdir(path) == 0);
    vfs_stat_t st; CHECK(vfs_stat("file", &st) == 0);
    char expected[128] = "/"; memset(expected + 1, 'a', 110);
    strcpy(expected + 111, "/file");
    CHECK(strcmp(operation_path, expected) == 0);
    CHECK(vfs_chdir("/") == 0); cleanup_operations();
    return EXIT_SUCCESS;
}
