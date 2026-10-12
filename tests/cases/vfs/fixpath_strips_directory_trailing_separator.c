#include "vfs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    char path[] = "/test/subdir/";
    CHECK(vfs_fixpath(path) == path);
    CHECK(strcmp(path, "/test/subdir") == 0);
    return EXIT_SUCCESS;
}
