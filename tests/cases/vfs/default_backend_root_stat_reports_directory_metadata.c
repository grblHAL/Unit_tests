#include "vfs.h"
#include "check.h"
#include <string.h>

int main(void)
{
    const vfs_t *backend = vfs_get_drive("/")->fs;
    vfs_stat_t st = {0};
    CHECK(backend->fstat("", &st) == 0);
    CHECK(st.st_mode.directory && st.st_mode.read_only && st.st_mode.hidden);
    CHECK(st.st_size > 0);
    return EXIT_SUCCESS;
}
