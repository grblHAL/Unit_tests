#include "vfs.h"
#include "check.h"
#include <string.h>
int main(void)
{
    char cwd[16] = "unchanged";
    CHECK(vfs_getcwd(cwd, 1) == NULL);
    CHECK(strcmp(cwd, "unchanged") == 0);
    return EXIT_SUCCESS;
}
