#include "sd_host.h"
int main(void)
{
    sd_prepare(false);
    char name[] = "/job.nc";
    CHECK(stream_file(STATE_IDLE, name) == Status_FsNotMounted);
    sd_mount();
    CHECK(stream_file(STATE_CYCLE, name) == Status_SystemGClock);
    char missing[] = "/missing.nc";
    CHECK(stream_file(STATE_IDLE, missing) == Status_FileOpenFailed);
    CHECK(!fs_busy() && hal.stream.read == sd_serial_read && sd_statuses == 0);
    return 0;
}
