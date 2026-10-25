#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    char name[] = "/JOB.NC";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK && fs_busy());
    stream_job_t *job = stream_get_job_info();
    CHECK(job && job->size == 9);
    char data[10];
    for (unsigned i = 0; i < 9; i++)
    {
        int32_t c = hal.stream.read();
        CHECK(c != SERIAL_NO_DATA);
        data[i] = (char)c;
    }
    data[9] = 0;
    CHECK(!strcmp(data, "G1X1\nM30\n"));
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(!fs_busy() && !stream_get_job_info() && hal.stream.read == sd_serial_read &&
          sd_completions == 1);
    vfs_file_t *f = vfs_open("/JOB.NC", "r");
    CHECK(f && f->size == 9);
    vfs_close(f);
    return 0;
}
