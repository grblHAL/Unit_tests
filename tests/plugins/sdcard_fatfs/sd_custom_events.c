#include "sd_controller_host.h"
int main(void)
{
    sd_prepare();
    sd_custom_events();
    CHECK(sd_command("FM") == Status_OK && sd_custom_mounts == 1);
    fatfs_put_file("/CUSTOM.NC", "G0", 2);
    CHECK(sd_command("FU") == Status_OK && sd_custom_unmounts == 1);
    CHECK(sd_command("FM") == Status_OK && sd_custom_mounts == 2);
    vfs_file_t *f = vfs_open("/CUSTOM.NC", "r");
    CHECK(f && f->size == 2);
    vfs_close(f);
    return 0;
}
