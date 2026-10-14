#include "vfs.h"
#include "check.h"
#include <string.h>
int main(void)
{
    const vfs_t *backend = vfs_get_drive("/")->fs;
    char data[8] = "fixture";
    CHECK(backend->fopen("missing.nc", "r") == NULL);
    CHECK(backend->fread(data, 1, sizeof(data), NULL) == 0);
    CHECK(backend->fwrite(data, 1, sizeof(data), NULL) == 0);
    CHECK(strcmp(data, "fixture") == 0);
    return EXIT_SUCCESS;
}
