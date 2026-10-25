#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    char name[] = "/JOB.NC";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    CHECK(hal.stream.read() == 'G');
    CHECK(grbl.report.status_message(Status_GcodeValueOutOfRange) == Status_GcodeValueOutOfRange);
    CHECK(!fs_busy() && sd_flushes == 1 && strstr(sd_output, "in SD file at line 1"));
    CHECK(stream_file(STATE_IDLE, name) == Status_OK && hal.stream.read() == 'G');
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(!fs_busy());
    return 0;
}
