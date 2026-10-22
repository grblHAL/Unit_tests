#include "vfs.h"
#include "check.h"
#include <string.h>

int main(void)
{
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/", &st) == 0);
    CHECK(st.st_mode.directory && st.st_mode.read_only);
    CHECK(st.st_size > 0);
    return EXIT_SUCCESS;
}
