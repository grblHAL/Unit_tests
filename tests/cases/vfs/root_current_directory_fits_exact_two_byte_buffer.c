#include "vfs.h"
#include "check.h"
#include <string.h>
int main(void)
{
    char cwd[2] = "x";
    CHECK(vfs_getcwd(cwd, sizeof(cwd)) == cwd);
    CHECK(strcmp(cwd, "/") == 0);
    return EXIT_SUCCESS;
}
