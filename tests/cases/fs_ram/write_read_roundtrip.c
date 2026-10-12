#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "check.h"

int main(void)
{
    fs_ram_mount(); vfs_file_t *file = vfs_open("/ram/job", "w"); CHECK(file != NULL);
    CHECK(vfs_write("G1 X10", 1, 6, file) == 6); backend_close(file);
    file = vfs_open("/ram/job", "r"); CHECK(file != NULL); CHECK(file->status.is_temporary);
    char buffer[8] = {0}; CHECK(vfs_read(buffer, 1, 7, file) == 6); CHECK(strcmp(buffer, "G1 X10") == 0);
    CHECK(vfs_eof(file)); CHECK(vfs_read(buffer, 1, 1, file) == 0); backend_close(file);
    CHECK(vfs_open("/ram/job", "r") == NULL);
    return EXIT_SUCCESS;
}
