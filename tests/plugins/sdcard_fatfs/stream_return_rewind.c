#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    char name[] = "/JOB.NC";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    CHECK(hal.stream.read() == 'G');
    CHECK(hal.stream.read() == '1');
    grbl.on_program_completed(ProgramFlow_Return, false);
    CHECK(fs_busy() && stream_get_job_info()->pos == 0);
    CHECK(stream_get_job_info()->line_number == 1);
    CHECK(hal.stream.read() == 'G');
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(!fs_busy() && sd_completions == 2);
    return 0;
}
