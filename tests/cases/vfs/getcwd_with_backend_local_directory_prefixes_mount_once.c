#include "support/vfs_operations_host.h"
static char *backend_getcwd(char *buffer, size_t size) { (void)buffer; (void)size; return backend_directory; }
int main(void)
{
    operation_fs.fgetcwd = backend_getcwd;
    prepare_operations((vfs_st_mode_t){0}); CHECK(vfs_chdir("/store/dir") == 0);
    char cwd[64]; CHECK(vfs_getcwd(cwd, sizeof(cwd)) != NULL);
    CHECK(strcmp(cwd, "/store/dir") == 0); cleanup_operations();
    return EXIT_SUCCESS;
}
