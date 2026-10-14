#include "support/vfs_resource_host.h"
int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    char path[128] = "/store/"; memset(path + 7, 'a', 110); path[117] = 0;
    /* Current core grows the cached directory using realloc(NULL, size). */
    rejected_size = strlen(path) + 1; reject_realloc = 1;
    CHECK(vfs_chdir(path) == -1 && realloc_failures == 1);
    CHECK(chdir_calls == 1);
    char cwd[16]; CHECK(vfs_getcwd(cwd, sizeof(cwd)) != NULL);
    CHECK(strcmp(cwd, "/") == 0); cleanup_operations();
    return EXIT_SUCCESS;
}
