#include "sd_controller_host.h"
int main(void)
{
    sd_prepare();
    sd_startup();
    CHECK(sd_command("FU") == Status_SDNotMounted);
    CHECK(sd_command("FM") == Status_OK && sdcard_getfs());
    fatfs_put_file("/JOB.NC", "G0", 2);
    sd_report(false);
    CHECK(!strcmp(sd_output, "|SD:3|previous"));
    sd_report(false);
    CHECK(!strcmp(sd_output, "|previous"));
    CHECK(sd_command("FU") == Status_OK);
    sd_report(false);
    CHECK(!strcmp(sd_output, "|SD:2|previous"));
    CHECK(!vfs_open("/JOB.NC", "r"));
    CHECK(sd_command("FM") == Status_OK);
    vfs_file_t *f = vfs_open("/JOB.NC", "r");
    CHECK(f && f->size == 2);
    vfs_close(f);
    return 0;
}
