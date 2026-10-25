#include "sd_controller_host.h"
int main(void)
{
    sd_prepare();
    sd_startup();
    sdcard_detect(true);
    sd_run();
    sd_report(true);
    CHECK(!strcmp(sd_output, "|SD:3|previous"));
    sdcard_detect(false);
    sd_run();
    sd_report(true);
    CHECK(!strcmp(sd_output, "|SD:2|previous"));
    sdcard_detect(true);
    sd_run();
    CHECK(sdcard_getfs());
    fatfs_put_file("/JOB.NC", "G0", 2);
    return 0;
}
