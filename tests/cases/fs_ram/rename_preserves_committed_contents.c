#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "check.h"

int main(void)
{
    fs_ram_mount();
    vfs_file_t *file = vfs_open("/ram/original", "w");
    CHECK(file != NULL);
    CHECK(vfs_write("G1X5", 1, 4, file) == 4);
    backend_close(file);
    CHECK(vfs_rename("/ram/original", "/ram/renamed") == 0);
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/ram/original", &st) == -1);
    CHECK(vfs_stat("/ram/renamed", &st) == 0);
    CHECK(st.st_size == 4);
    file = vfs_open("/ram/renamed", "r");
    CHECK(file != NULL);
    char data[5] = {0};
    CHECK(vfs_read(data, 1, 4, file) == 4);
    CHECK(strcmp(data, "G1X5") == 0);
    backend_close(file);
    return EXIT_SUCCESS;
}
