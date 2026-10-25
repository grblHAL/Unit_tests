#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    char name[] = "/JOB.NC";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    sd_state = STATE_CYCLE;
    for (unsigned i = 0; i < 9; i++) CHECK(hal.stream.read() != SERIAL_NO_DATA);
    sd_clear_output();
    grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){0});
    CHECK(strstr(sd_output, "|SD:99.9,JOB.NC"));
    sd_clear_output();
    grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){.all = On});
    CHECK(!strstr(sd_output, "|SD:"));
    sd_state = STATE_IDLE;
    sd_clear_output();
    grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){0});
    CHECK(strstr(sd_output, "|SD:100.0,JOB.NC"));
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(stream_get_job_info() == NULL);
    return 0;
}
