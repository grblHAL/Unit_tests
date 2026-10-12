#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "check.h"

int main(void)
{
    fs_ram_mount(); char path[70] = "/ram/"; memset(path + 5, 'a', 33); path[38] = 0;
    CHECK(vfs_open(path, "w") == NULL); path[37] = 0; CHECK(vfs_open(path, "w") == NULL); path[36] = 0; vfs_file_t *file = vfs_open(path, "w"); CHECK(file != NULL); backend_close(file);
    return EXIT_SUCCESS;
}
