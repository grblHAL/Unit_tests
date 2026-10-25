#include "job_host.h"
int main(void)
{
    job_prepare();
    const uint8_t stitches[] = {0xa0, 30, 0xa0, 40, 1, 1, 0xff};
    vfs_file_t *file = job_pes(stitches, sizeof(stitches));
    CHECK(grbl.on_file_open("job.pes", file, true) == Status_OK);
    for (unsigned i = 0; i < 4; i++)
        CHECK(hal.stream.read() == SERIAL_NO_DATA);
    grbl.on_execute_realtime(STATE_IDLE);
    job_run_tasks();
    CHECK(job_holds == 1 && job_motion_count == 0);
    sys.rt_exec_state &= ~EXEC_FEED_HOLD;
    grbl.on_state_change(STATE_IDLE);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 1 && job_motions[0].rapid);
    CHECK(job_motions[0].target.x == 3 && job_motions[0].target.y == -4);
    job_run_tasks();
    CHECK(job_holds == 2 && job_syncs == 2 && strstr(job_output, "trim"));
    for (unsigned i = 0; i < 4; i++)
        grbl.on_execute_realtime(STATE_HOLD);
    CHECK(job_motion_count == 1 && !job_spindle_on);
    sys.rt_exec_state &= ~EXEC_FEED_HOLD;
    grbl.on_state_change(STATE_IDLE);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 2 && !job_motions[1].rapid && job_spindle_on);
    CHECK(fabsf(job_motions[1].target.x - 3.1f) < .0001f);
    CHECK(fabsf(job_motions[1].target.y + 4.1f) < .0001f);
    job_needle();
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_completions == 1 && !job_spindle_on);
    return 0;
}
