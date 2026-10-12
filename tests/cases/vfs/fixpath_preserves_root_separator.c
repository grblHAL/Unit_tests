#include "vfs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    char path[] = "/";
    CHECK(vfs_fixpath(path) == path);
    CHECK(strcmp(path, "/") == 0);
    return EXIT_SUCCESS;
}
