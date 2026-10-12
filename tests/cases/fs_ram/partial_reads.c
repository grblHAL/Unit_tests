#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "check.h"

int main(void)
{
    fs_ram_mount(); vfs_file_t *file = vfs_open("/ram/job", "w"); CHECK(file != NULL);
    CHECK(vfs_write("abcdef", 1, 6, file) == 6); backend_close(file);
    file = vfs_open("/ram/job", "r"); CHECK(file != NULL);
    char buffer[4] = {0}; CHECK(vfs_read(buffer, 1, 2, file) == 2); CHECK(strcmp(buffer, "ab") == 0); CHECK(vfs_tell(file) == 2);
    CHECK(!vfs_eof(file)); CHECK(vfs_read(buffer, 1, 3, file) == 3); CHECK(memcmp(buffer, "cde", 3) == 0); CHECK(vfs_tell(file) == 5);
    backend_close(file);
    return EXIT_SUCCESS;
}
