#include "vfs.h"
#include "check.h"
#include <string.h>

int main(void)
{
    const vfs_t *backend = vfs_get_drive("/")->fs;
    char path[160]; memset(path, 'x', sizeof(path) - 1); path[sizeof(path) - 1] = 0;
    vfs_stat_t st = {.st_size = 456, .st_mode = {.archive = true}};
    CHECK(backend->fstat(path, &st) != 0);
    CHECK(st.st_size == 456 && st.st_mode.archive && !st.st_mode.directory);
    return EXIT_SUCCESS;
}
