#include "support/vfs_operations_host.h"

int main(void)
{
    operation_fs.fgetcwd = NULL;
    operation_fs.fchdir = NULL;
    prepare_operations((vfs_st_mode_t){0}); CHECK(vfs_chdir("/store/dir") == 0);
    char cwd[64]; CHECK(vfs_getcwd(cwd, sizeof(cwd)) != NULL);
    fprintf(stderr, "cwd=%s, expected /store/dir\n", cwd);
    CHECK(strcmp(cwd, "/store/dir") == 0); cleanup_operations();
    return EXIT_SUCCESS;
}
