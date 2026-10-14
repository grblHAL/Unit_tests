#include "vfs.h"
#include "check.h"
int main(void)
{
    const vfs_t *backend = vfs_get_drive("/")->fs;
    CHECK(backend->ftell(NULL) == 0);
    CHECK(backend->fseek(NULL, 10) == -1);
    CHECK(backend->feof(NULL));
    backend->fclose(NULL);
    return EXIT_SUCCESS;
}
