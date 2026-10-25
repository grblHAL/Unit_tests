#include "fatfs_host.h"
int main(void)
{
    fatfs_prepare();
    CHECK(vfs_mkdir("/JOBS") == FR_OK && vfs_chdir("/JOBS") == 0);
    char path[64];
    CHECK(vfs_getcwd(path, sizeof(path)) && !strcmp(path, "/JOBS"));
    fatfs_put_file("PART.NC", "G0X1", 4);
    vfs_free_t *space = vfs_fgetfree("/JOBS");
    CHECK(space && space->size > 1000000 && space->used < space->size);
    vfs_file_t *f = vfs_open("PART.NC", "r");
    CHECK(f && f->size == 4);
    vfs_close(f);
    return 0;
}
