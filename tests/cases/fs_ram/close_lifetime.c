#include "hal.h"
#include "fs_ram.h"
#include "vfs.h"
#include "check.h"
static void changed(const vfs_t *fs)
{
    (void)fs;
}
int main(void)
{
    vfs.on_fs_changed = changed;
    fs_ram_mount();
    CHECK(vfs_mount_set_mode("/ram", (vfs_st_mode_t){.directory = On}));
    vfs_file_t *file = vfs_open("/ram/close", "w");
    CHECK(file != NULL);
    CHECK(vfs_write("hello", 1, 5, file) == 5);
    vfs_close(file);
    return EXIT_SUCCESS;
}
