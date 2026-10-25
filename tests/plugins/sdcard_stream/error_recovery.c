#include "sd_host.h"
int main(void)
{
    sd_prepare(true);
    char name[] = "/job.nc";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    CHECK(hal.stream.read() == 'G');
    CHECK(grbl.report.status_message(Status_GcodeValueOutOfRange) == Status_GcodeValueOutOfRange);
    CHECK(!fs_busy() && sd_flushes == 1 && sd_statuses == 2);
    CHECK(strstr(sd_output, "in SD file at line 1"));
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(!fs_busy() && sd_completions == 1);
    return 0;
}
