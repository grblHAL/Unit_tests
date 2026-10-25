#include "sd_controller_host.h"
int main(void)
{
    sd_detectable = false;
    settings.fs_options.sd_mount_on_boot = On;
    sd_prepare();
    sd_startup();
    CHECK(sdcard_getfs());
    sd_report(true);
    CHECK(!strcmp(sd_output, "|SD:1|previous"));
    sd_output[0] = 0;
    grbl.on_report_options(true);
    CHECK(!strcmp(sd_output, ",SD"));
    grbl.on_report_options(false);
    CHECK(sd_options == 2 && sd_plugins == 1);
    return 0;
}
