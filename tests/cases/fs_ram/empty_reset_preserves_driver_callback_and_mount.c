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
    CHECK(hal.driver_reset != driver_reset);
    hal.driver_reset();
    CHECK(resets == 1);
    CHECK(vfs_fgetfree("/ram/")->used == 0);
    vfs_file_t *file = vfs_open("/ram/after-reset", "w");
    CHECK(file != NULL);
    CHECK(vfs_write("ok", 1, 2, file) == 2);
    backend_close(file);
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/ram/after-reset", &st) == 0);
    CHECK(st.st_size == 2);
    return EXIT_SUCCESS;
}
