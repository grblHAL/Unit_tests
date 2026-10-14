#include "support/vfs_operations_host.h"
int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    char first[128] = "/store/", second[144] = "/store/";
    memset(first + 7, 'a', 110); first[117] = 0;
    memset(second + 7, 'b', 120); second[127] = 0;
    CHECK(vfs_chdir(first) == 0 && vfs_chdir(second) == 0);
    vfs_stat_t st; CHECK(vfs_stat("file", &st) == 0);
    char expected[144] = "/"; memset(expected + 1, 'b', 120);
    strcpy(expected + 121, "/file");
    CHECK(strcmp(operation_path, expected) == 0);
    CHECK(vfs_chdir("/") == 0); cleanup_operations();
    return EXIT_SUCCESS;
}
