#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "check.h"

int main(void)
{
    fs_ram_mount(); vfs_file_t *file = vfs_open("/ram/job", "w"); CHECK(file != NULL);
    CHECK(vfs_write(NULL, 0, 10, file) == 0); CHECK(vfs_write(NULL, 10, 0, file) == 0); backend_close(file);
    file = vfs_open("/ram/job", "r"); CHECK(file != NULL); CHECK(vfs_eof(file)); backend_close(file);
    return EXIT_SUCCESS;
}
