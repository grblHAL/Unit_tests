#include "hal.h"
#include "vfs.h"
#include "check.h"
#include <string.h>

static unsigned rtc_calls;
static bool clock_available;
static bool read_clock(struct tm *time)
{
    rtc_calls++;
    if(!clock_available) return false;
    *time = (struct tm){.tm_year = 126, .tm_mon = 9, .tm_mday = 23, .tm_hour = 12};
    return true;
}

int main(void)
{
    static const vfs_t fs = {.fs_name = "fixture"};
    hal.rtc.get_datetime = read_clock;
    for(unsigned attempt = 0; attempt < 2; attempt++) {
        clock_available = attempt != 0;
        CHECK(vfs_mount(NULL, "/store", &fs, (vfs_st_mode_t){.directory = true}));
        CHECK(rtc_calls == attempt + 1);
        vfs_drive_t *drive = vfs_get_drive("/store/program.nc");
        CHECK(drive != NULL && drive->fs == &fs);
        CHECK(strcmp(drive->path, "/store/") == 0);
        CHECK(vfs_unmount(NULL, "/store"));
    }
    return EXIT_SUCCESS;
}
