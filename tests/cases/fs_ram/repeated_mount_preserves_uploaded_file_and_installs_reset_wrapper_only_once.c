#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "support/mount_result_host.h"
static unsigned resets;
static void driver_reset(void) { resets++; }
int main(void)
{
    hal.driver_reset = driver_reset;
    CHECK_MOUNT_RESULT(fs_ram_mount(), true);
    driver_reset_ptr wrapper = hal.driver_reset;
    CHECK(wrapper != driver_reset);
    vfs_file_t *file = vfs_open("/ram/job", "w");
    CHECK(file != NULL && vfs_write("G1X1\n", 1, 5, file) == 5);
    backend_close(file);
    CHECK_MOUNT_RESULT(fs_ram_mount(), false);
    CHECK(hal.driver_reset == wrapper && resets == 0);
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/ram/job", &st) == 0 && st.st_size == 5);
    CHECK(vfs_fgetfree("/ram/")->used == 5);
    hal.driver_reset();
    CHECK(resets == 1 && hal.driver_reset == wrapper);
    CHECK(vfs_stat("/ram/job", &st) == -1);
    CHECK(vfs_fgetfree("/ram/")->used == 0);
    CHECK_MOUNT_RESULT(fs_ram_mount(), false);
    CHECK(hal.driver_reset == wrapper);
    hal.driver_reset();
    CHECK(resets == 2 && hal.driver_reset == wrapper);
    file = vfs_open("/ram/next", "w");
    CHECK(file != NULL && vfs_write("ok", 1, 2, file) == 2);
    backend_close(file);
    CHECK(vfs_stat("/ram/next", &st) == 0 && st.st_size == 2);
    return EXIT_SUCCESS;
}
