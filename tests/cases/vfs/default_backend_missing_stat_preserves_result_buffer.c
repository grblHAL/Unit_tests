#include "vfs.h"
#include "check.h"
#include <string.h>

int main(void)
{
    const vfs_t *backend = vfs_get_drive("/")->fs;
    vfs_stat_t st = {.st_size = 123, .st_mode = {.archive = true}};
    vfs_stat_t before = st;
    CHECK(backend->fstat("missing.nc", &st) != 0);
    CHECK(st.st_size == before.st_size && st.st_mode.mode == before.st_mode.mode);
    return EXIT_SUCCESS;
}
