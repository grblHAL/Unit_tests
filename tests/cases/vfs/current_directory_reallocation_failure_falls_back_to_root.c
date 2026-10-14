#include "support/vfs_resource_host.h"
int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    char first[128] = "/store/", second[144] = "/store/";
    memset(first + 7, 'a', 110); first[117] = 0;
    memset(second + 7, 'b', 120); second[127] = 0;
    CHECK(vfs_chdir(first) == 0);
    rejected_size = strlen(second) + 1; reject_realloc = 1;
    CHECK(vfs_chdir(second) == -1 && realloc_failures == 1);
    char cwd[16]; CHECK(vfs_getcwd(cwd, sizeof(cwd)) != NULL);
    CHECK(strcmp(cwd, "/") == 0); cleanup_operations();
    return EXIT_SUCCESS;
}
