#include "vfs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    char *path = vfs_getcwd(NULL, 0);
    CHECK(path != NULL);
    CHECK(strcmp(path, "/") == 0);
    free(path);
    return EXIT_SUCCESS;
}
