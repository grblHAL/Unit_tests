#include "sd_controller_host.h"
int main(void)
{
    settings.fs_options.sd_mount_on_boot = On;
    fatfs_present = false;
    sd_prepare();
    sd_startup();
    CHECK(sd_messages == 1 && strstr(sd_output, "automount failed"));
    fatfs_present = true;
    CHECK(sd_command("FM") == Status_OK);
    fatfs_put_file("/JOB.NC", "G0", 2);
    CHECK(sd_messages == 1);
    return 0;
}
