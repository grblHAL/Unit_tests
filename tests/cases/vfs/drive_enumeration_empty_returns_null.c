#include "vfs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    CHECK(vfs_drives_open() == NULL);
    return EXIT_SUCCESS;
}
