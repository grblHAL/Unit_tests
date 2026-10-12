#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "check.h"

int main(void)
{
    fs_ram_mount();
    CHECK(vfs_mount_set_mode("/ram", (vfs_st_mode_t){ .directory = true }));
    vfs_file_t *file = vfs_open("/ram/job", "w");
    CHECK(file != NULL);
    CHECK(vfs_write("hello", 1, 5, file) == 5);
    CHECK(vfs_unlink("/ram/job") == -1);
    backend_close(file);
    CHECK(vfs_unlink("/ram/job") == 0);
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/ram/job", &st) == -1);
    CHECK(vfs_unlink("/ram/job") == -1);
    CHECK(vfs_open("/ram/job", "r") == NULL);
    return EXIT_SUCCESS;
}
