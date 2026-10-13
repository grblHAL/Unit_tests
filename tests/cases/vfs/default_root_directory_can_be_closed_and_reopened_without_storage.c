#include "vfs.h"
#include "check.h"
#include <string.h>

int main(void)
{
    vfs_dir_t *dir = vfs_opendir("/");
    CHECK(dir != NULL);
    CHECK(vfs_readdir(dir) == NULL);
    vfs_closedir(dir);
    dir = vfs_opendir("/");
    CHECK(dir != NULL);
    CHECK(vfs_readdir(dir) == NULL);
    vfs_closedir(dir);
    return EXIT_SUCCESS;
}
