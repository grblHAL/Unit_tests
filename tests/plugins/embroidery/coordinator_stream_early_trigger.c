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
    CHECK(job_motion_count == 1);
    grbl.on_state_change(STATE_CYCLE);
    job_needle();
    grbl.on_execute_realtime(STATE_CYCLE);
    CHECK(job_motion_count == 1 && job_completions == 0);
    grbl.on_state_change(STATE_IDLE);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 1);
    job_needle();
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 2 && fabsf(job_motions[1].target.x - .2f) < .0001f);
    job_needle();
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_completions == 1 && !job_spindle_on);
    return 0;
}
