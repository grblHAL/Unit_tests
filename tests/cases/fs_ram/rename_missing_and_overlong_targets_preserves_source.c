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
    CHECK(vfs_rename("/ram/missing", "/ram/new") == -1);
    CHECK(vfs_rename("/ram/job", "/ram/abcdefghijklmnopqrstuvwxyz0123456789") == -1);
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/ram/job", &st) == 0);
    CHECK(st.st_size == 5);
    CHECK(vfs_stat("/ram/new", &st) == -1);
    return EXIT_SUCCESS;
}
