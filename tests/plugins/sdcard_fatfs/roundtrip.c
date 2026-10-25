#include "fatfs_host.h"
int main(void)
{
    fatfs_prepare();
    uint8_t data[1024], readback[1024];
    for (unsigned i = 0; i < sizeof(data); i++)
        data[i] = (i * 17 + 3) % 251;
    fatfs_put_file("/JOB.NC", data, sizeof(data));
    vfs_file_t *f = vfs_open("/JOB.NC", "r");
    CHECK(f && f->size == sizeof(data));
    CHECK(vfs_read(readback, 1, 100, f) == 100 && vfs_tell(f) == 100);
    CHECK(vfs_seek(f, 0) == FR_OK);
    CHECK(vfs_read(readback, 1, sizeof(readback), f) == sizeof(readback));
    CHECK(!memcmp(data, readback, sizeof(data)) && vfs_eof(f));
    CHECK(fatfs_reads && fatfs_writes);
    vfs_close(f);
    return 0;
}
