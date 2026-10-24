#include "sd_host.h"
int main(void)
{
    sd_prepare(true);
    char name[] = "/job.nc";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    CHECK(sd_rt_handler('X'));
    CHECK(sd_rt_handler(CMD_STATUS_REPORT) && sd_realtime == 2);
    CHECK(hal.stream.read() == 'G');
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(!sd_rt_handler('X') && sd_realtime == 3);
    return 0;
}
