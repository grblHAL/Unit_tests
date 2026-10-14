#include "support/vfs_operations_host.h"

int main(void)
{
    operation_fs.fchdir = NULL; stat_directory = false;
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_chdir("/store/file") == -1 && stat_calls == 1);
    char cwd[32]; CHECK(vfs_getcwd(cwd, sizeof(cwd)) != NULL);
    CHECK(strcmp(cwd, "/") == 0); cleanup_operations();
    return EXIT_SUCCESS;
}
