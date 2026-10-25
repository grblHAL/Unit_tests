#include "fatfs_host.h"
int main(void)
{
    fatfs_prepare();
    uint8_t data[1024];
    memset(data, 0x5a, sizeof(data));
    fatfs_put_file("/READ.NC", data, sizeof(data));
    vfs_file_t *f = vfs_open("/READ.NC", "r");
    CHECK(f);
    fatfs_read_error = true;
    CHECK(vfs_read(data, 1, sizeof(data), f) == 0 && vfs_errno == FR_DISK_ERR);
    fatfs_read_error = false;
    vfs_close(f);
    f = vfs_open("/READ.NC", "r");
    CHECK(f && vfs_read(data, 1, sizeof(data), f) == sizeof(data));
    for (unsigned i = 0; i < sizeof(data); i++)
        CHECK(data[i] == 0x5a);
    vfs_close(f);
    return 0;
}
