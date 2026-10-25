#include "fatfs_host.h"
int main(void)
{
    fatfs_prepare();
    CHECK(!vfs_open("/MISSING.NC", "r") && vfs_errno == FR_NO_FILE);
    CHECK(!vfs_opendir("/MISSING"));
    fatfs_put_file("/NEXT.NC", "G0", 2);
    vfs_file_t *f = vfs_open("/NEXT.NC", "r");
    CHECK(f);
    vfs_close(f);
    return 0;
}
