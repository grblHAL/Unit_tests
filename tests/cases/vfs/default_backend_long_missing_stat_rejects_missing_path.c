#include "vfs.h"
#include "check.h"
#include <string.h>
#include <errno.h>

int main(void)
{
    char path[160]; memset(path, 'x', sizeof(path) - 1); path[sizeof(path) - 1] = 0;
    vfs_stat_t st = {.st_size = 456, .st_mode = {.archive = true}};
    CHECK(vfs_stat(path, &st) != 0);
    CHECK(vfs_errno == ENOTDIR);
    return EXIT_SUCCESS;
}
