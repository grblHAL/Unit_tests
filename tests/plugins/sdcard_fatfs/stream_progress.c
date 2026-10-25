#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    char name[] = "/JOB.NC";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    CHECK(hal.stream.read() == 'G' && stream_get_job_info()->pos == 1);
    sd_clear_output();
    grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){0});
    CHECK(strstr(sd_output, "|SD:11.1,JOB.NC"));
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    return 0;
}
