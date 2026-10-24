#include "sd_host.h"
int main(void)
{
    sd_prepare(true);
    char name[] = "/job.nc";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    CHECK(hal.stream.read() == 'G');
    hal.driver_reset();
    CHECK(sd_resets == 1 && sd_flushes == 1 && !fs_busy() && hal.stream.read == sd_serial_read);
    CHECK(strstr(sd_output, "Reset during streaming"));
    return 0;
}
