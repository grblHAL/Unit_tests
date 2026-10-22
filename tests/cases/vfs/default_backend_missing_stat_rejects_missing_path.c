#include "vfs.h"
#include "check.h"
#include <string.h>
#include <errno.h>

int main(void)
{
    vfs_stat_t st = {.st_size = 123, .st_mode = {.archive = true}};
    CHECK(vfs_stat("missing.nc", &st) != 0);
    CHECK(vfs_errno == ENOTDIR);
    return EXIT_SUCCESS;
}
