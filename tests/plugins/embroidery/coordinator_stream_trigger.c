#include "job_host.h"
int main(void)
{
    job_prepare();
    const uint8_t stitches[] = {1, 0, 3, 1, 0, 3, 0, 0, 0xf3};
    vfs_file_t *file = job_dst(stitches, sizeof(stitches));
    CHECK(grbl.on_file_open("job.dst", file, true) == Status_OK);
    for (unsigned i = 0; i < 3; i++)
        CHECK(hal.stream.read() == SERIAL_NO_DATA);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 1 && job_spindle_on);
    for (unsigned i = 0; i < 4; i++)
        grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 1 && job_completions == 0);
    job_needle();
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 2 && fabsf(job_motions[1].target.x - .2f) < .0001f);
    CHECK(job_motions[1].target.z == 0);
    job_needle();
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_completions == 1 && !job_spindle_on);
    CHECK(hal.stream.read == job_serial_read);
    return 0;
}
