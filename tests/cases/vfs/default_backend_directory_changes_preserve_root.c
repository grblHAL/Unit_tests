#include "vfs.h"
#include "check.h"
#include <string.h>

int main(void)
{
    const vfs_t *backend = vfs_get_drive("/")->fs;
    CHECK(backend->fchdir("/") == 0);
    CHECK(backend->fchdir("/missing") != 0);
    CHECK(backend->fmkdir("/new") != 0);
    CHECK(backend->frmdir("/") != 0);
    CHECK(backend->funlink("missing.nc") != 0);
    char cwd[8] = {0};
    CHECK(strcmp(vfs_getcwd(cwd, sizeof(cwd)), "/") == 0);
    return EXIT_SUCCESS;
}
