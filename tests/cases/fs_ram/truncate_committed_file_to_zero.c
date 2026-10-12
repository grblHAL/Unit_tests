#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "check.h"

int main(void)
{
    fs_ram_mount();
    vfs_file_t *file = vfs_open("/ram/job", "w");
    CHECK(file != NULL);
    CHECK(vfs_write("hello", 1, 5, file) == 5);
    backend_close(file);
    file = vfs_open("/ram/job", "r");
    CHECK(file != NULL);
    CHECK(vfs_truncate(file, 0) == 0);
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/ram/job", &st) == 0);
    CHECK(st.st_size == 0);
    CHECK(vfs_eof(file));
    char byte = 'x';
    CHECK(vfs_read(&byte, 1, 1, file) == 0);
    CHECK(byte == 'x');
    CHECK(vfs_truncate(file, 0) == 0);
    backend_close(file);
    return EXIT_SUCCESS;
}
