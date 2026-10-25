#include "sd_controller_host.h"
int main(void)
{
    sd_prepare();
    sdcard_early_mount();
    CHECK(hal.driver_setup(&settings));
    CHECK(sd_setups == 1 && sd_changes == 1 && sdcard_getfs());
    fatfs_put_file("/EARLY.NC", "G0", 2);
    CHECK(hal.driver_setup(&settings) && sd_changes == 2);
    CHECK(sdcard_getfs());
    return 0;
}
