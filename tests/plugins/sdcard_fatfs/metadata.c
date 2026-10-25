#include "fatfs_host.h"
int main(void)
{
    fatfs_prepare();
    fatfs_put_file("/TIME.NC", "G0", 2);
    vfs_stat_t st;
    CHECK(vfs_stat("/TIME.NC", &st) == 0 && st.st_size == 2 && !st.st_mode.directory);
    struct tm modified = {
        .tm_year = 125, .tm_mon = 5, .tm_mday = 14, .tm_hour = 10, .tm_min = 20, .tm_sec = 30};
    CHECK(vfs_utime("/TIME.NC", &modified) == FR_OK);
    CHECK(vfs_stat("/TIME.NC", &st) == 0);
    struct tm *time = localtime(&st.st_mtime);
    CHECK(time && time->tm_year == 125 && time->tm_mon == 5 && time->tm_mday == 14 &&
          time->tm_sec == 30);
    return 0;
}
