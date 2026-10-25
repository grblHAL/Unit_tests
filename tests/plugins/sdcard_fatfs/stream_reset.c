#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    char name[] = "/JOB.NC";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    CHECK(hal.stream.read() == 'G');
    hal.driver_reset();
    CHECK(sd_resets == 1 && sd_flushes == 1 && !fs_busy() && hal.stream.read == sd_serial_read);
    CHECK(stream_file(STATE_IDLE, name) == Status_OK && hal.stream.read() == 'G');
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(!fs_busy());
    return 0;
}
