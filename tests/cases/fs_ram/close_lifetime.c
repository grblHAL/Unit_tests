#include "hal.h"
#include "fs_ram.h"
#include "vfs.h"
#include "check.h"
static const vfs_t *expected_fs;
static unsigned notifications;
static void changed(const vfs_t *fs)
{
    CHECK(fs == expected_fs);
    notifications++;
    /* The file must already be closed when its change notification runs. */
    CHECK(fs->funlink("/close") == 0);
}
int main(void)
{
    fs_ram_mount();
    CHECK(vfs_mount_set_mode("/ram", (vfs_st_mode_t){.directory = On}));
    vfs_file_t *file = vfs_open("/ram/close", "w");
    CHECK(file != NULL);
    expected_fs = file->fs;
    vfs.on_fs_changed = changed;
    CHECK(vfs_write("hello", 1, 5, file) == 5);
    CHECK(expected_fs->funlink("/close") == -1);
    vfs_close(file);
    CHECK(notifications == 1);
    CHECK(vfs_open("/ram/close", "r") == NULL);
    return EXIT_SUCCESS;
}
