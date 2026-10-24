#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "check.h"

static unsigned resets;
static void driver_reset(void) { resets++; }

int main(void)
{
    hal.driver_reset = driver_reset;
    fs_ram_mount();
    vfs_file_t *file = vfs_open("/ram/before-reset", "w");
    CHECK(file != NULL);
    CHECK(vfs_write("hello", 1, 5, file) == 5);
    backend_close(file);
    file = vfs_open("/ram/empty-upload", "w");
    CHECK(file != NULL);
    backend_close(file);
    vfs_stat_t empty = {0};
    CHECK(vfs_stat("/ram/empty-upload", &empty) == 0 && empty.st_size == 0);
    CHECK(vfs_fgetfree("/ram/")->used == 5);
    hal.driver_reset();
    CHECK(resets == 1);
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/ram/before-reset", &st) == -1);
    CHECK(vfs_stat("/ram/empty-upload", &st) == -1);
    CHECK(vfs_fgetfree("/ram/")->used == 0);
    file = vfs_open("/ram/after-reset", "w");
    CHECK(file != NULL);
    CHECK(vfs_write("ok", 1, 2, file) == 2);
    backend_close(file);
    CHECK(vfs_stat("/ram/after-reset", &st) == 0);
    CHECK(st.st_size == 2);
    file = vfs_open("/ram/after-reset", "r");
    CHECK(file != NULL);
    char contents[3] = {0};
    CHECK(vfs_read(contents, 1, 2, file) == 2 && strcmp(contents, "ok") == 0);
    backend_close(file);
    return EXIT_SUCCESS;
}
