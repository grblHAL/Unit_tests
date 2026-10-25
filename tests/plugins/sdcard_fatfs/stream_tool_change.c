#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    char name[] = "/JOB.NC";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    CHECK(hal.stream.read() == 'G');
    CHECK(hal.stream.suspend_read(true));
    CHECK(hal.stream.read() == SERIAL_NO_DATA);
    CHECK(sd_rt_handler(CMD_STATUS_REPORT) && sd_realtime == 1);
    CHECK(sd_rt_handler(CMD_TOOL_ACK) && sd_acks == 1);
    CHECK(hal.stream.suspend_read(false) && hal.stream.read() == '1');
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(!fs_busy());
    return 0;
}
