#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "check.h"

int main(void)
{
    fs_ram_mount(); vfs_file_t *file = vfs_open("/ram/job", "w"); CHECK(file != NULL);
    vfs_write("abcdef", 1, 6, file); backend_close(file); file = vfs_open("/ram/job", "r"); CHECK(file != NULL);
    CHECK(vfs_seek(file, 3) == 0); CHECK(vfs_tell(file) == 3); char byte; CHECK(vfs_read(&byte, 1, 1, file) == 1); CHECK(byte == 'd');
    CHECK(vfs_seek(file, 6) == 0); CHECK(vfs_eof(file)); CHECK(vfs_seek(file, 7) == -1); CHECK(vfs_tell(file) == 6);
    CHECK(vfs_seek(file, 0) == 0); CHECK(!vfs_eof(file)); backend_close(file);
    return EXIT_SUCCESS;
}
