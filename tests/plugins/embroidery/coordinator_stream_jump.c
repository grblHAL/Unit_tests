#include "job_host.h"
int main(void)
{
    job_prepare();
    const uint8_t stitches[] = {1, 0, 3, 1, 0, 3, 1, 0, 0x83, 1, 0, 3, 0, 0, 0xf3};
    vfs_file_t *file = job_dst(stitches, sizeof(stitches));
    CHECK(grbl.on_file_open("job.dst", file, true) == Status_OK);
    for (unsigned i = 0; i < 5; i++)
        CHECK(hal.stream.read() == SERIAL_NO_DATA);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 1 && job_spindle_on && !job_mist_on);
    job_needle();
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 2 && !job_motions[1].rapid && job_spindle_on);
    CHECK(job_mist_on);
    job_needle();
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 3 && job_motions[2].rapid);
    CHECK(fabsf(job_motions[2].target.x - .3f) < .0001f);
    CHECK(job_mist_on && !job_spindle_on);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 3);
    grbl.on_state_change(STATE_CYCLE);
    grbl.on_state_change(STATE_IDLE);
    CHECK(!job_mist_on && job_mist_writes == 2);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 4 && !job_motions[3].rapid && job_spindle_on);
    CHECK(fabsf(job_motions[3].target.x - .4f) < .0001f);
    job_needle();
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_completions == 1 && !job_spindle_on);
    return 0;
}
