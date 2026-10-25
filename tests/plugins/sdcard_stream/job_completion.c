#include "sd_host.h"
int main(void)
{
    sd_prepare(true);
    char name[] = "/job.nc";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    CHECK(fs_busy() && sd_statuses == 1);
    stream_job_t *job = stream_get_job_info();
    CHECK(job && job->size == 11 && !strcmp(job->name, "job.nc"));
    char data[32];
    sd_read(data, sizeof(data));
    CHECK(!strcmp(data, "G1X1\nM30\nXX\n"));
    CHECK(!fs_busy() && hal.stream.read == sd_serial_read && sd_completions == 1 &&
          sd_feedback == 1 && sd_flushes == 1);
    CHECK(stream_get_job_info() == NULL);
    return 0;
}
