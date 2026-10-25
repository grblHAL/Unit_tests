#include "sd_controller_host.h"
int main(void)
{
    sd_present = false;
    sd_prepare();
    sdcard_early_mount();
    CHECK(hal.driver_setup(&settings) && sd_changes == 1);
    sd_report(true);
    CHECK(!strcmp(sd_output, "|previous"));
    CHECK(sd_command("FU") == Status_SDNotMounted);
    sd_present = true;
    sdcard_detect(true);
    sd_run();
    CHECK(sdcard_getfs());
    return 0;
}
