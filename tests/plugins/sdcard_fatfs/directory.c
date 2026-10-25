#include "fatfs_host.h"
int main(void)
{
    fatfs_prepare();
    CHECK(vfs_mkdir("/JOBS") == FR_OK);
    fatfs_put_file("/JOBS/PART.NC", "G0X1\n", 5);
    fatfs_put_file("/JOBS/SYSTEM.NC", "G0X2\n", 5);
    CHECK(vfs_chmod("/JOBS/SYSTEM.NC", (vfs_st_mode_t){.system = On},
                    (vfs_st_mode_t){.system = On}) == 0);
    vfs_dir_t *dir = vfs_opendir("/JOBS");
    CHECK(dir);
    vfs_dirent_t *entry = vfs_readdir(dir);
    CHECK(entry && !strcmp(entry->name, "PART.NC") && entry->size == 5);
    CHECK(!vfs_readdir(dir));
    vfs_closedir(dir);
    return 0;
}
