#include "vfs.h"
#include "check.h"
#include <string.h>

int main(void)
{
    CHECK(vfs_open("/missing", "r") == NULL);
    CHECK(vfs_open("/missing", "w") == NULL);
    CHECK(vfs_opendir("/missing") == NULL);
    CHECK(vfs_unlink("/missing") != 0);
    CHECK(vfs_mkdir("/new") != 0);
    return EXIT_SUCCESS;
}
