#include "hal.h"
#include "fs_ram.h"
#include "vfs.h"
#include "check.h"
#include <string.h>

int main(void)
{
    fs_ram_mount();
    vfs_file_t *file = vfs_open("/ram/upload", "w");
    CHECK(file != NULL);
    CHECK(vfs_write("G1X99\n", 1, 6, file) == 6);
    CHECK(vfs_truncate(file, 0) == 0);
    CHECK(vfs_write("G1X1\n", 1, 5, file) == 5);
    vfs_close(file);
    file = vfs_open("/ram/upload", "r");
    CHECK(file != NULL);
    char program[32] = {0};
    size_t length = vfs_read(program, 1, sizeof(program), file);
    CHECK(vfs_eof(file));
    vfs_close(file);
    fprintf(stderr, "Replacement job length=%u contents=%s", (unsigned)length, program);
    CHECK(length == 5);
    CHECK(memcmp(program, "G1X1\n", 5) == 0);
    CHECK(vfs_open("/ram/upload", "r") == NULL);
    return EXIT_SUCCESS;
}
