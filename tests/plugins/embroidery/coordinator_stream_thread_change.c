#include "job_host.h"
int main(void)
{
    job_prepare();
    const uint8_t stitches[] = {10, 20, 0xff};
    vfs_file_t *file = job_pes(stitches, sizeof(stitches));
    CHECK(grbl.on_file_open("job.pes", file, true) == Status_OK);
    for (unsigned i = 0; i < 3; i++)
        CHECK(hal.stream.read() == SERIAL_NO_DATA);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 0 && job_holds == 0);
    job_run_tasks();
    CHECK(job_holds == 1 && job_syncs == 1);
    CHECK(strstr(job_output, embroidery_get_thread_color(5)));
    for (unsigned i = 0; i < 4; i++)
        grbl.on_execute_realtime(STATE_HOLD);
    CHECK(job_motion_count == 0 && !job_spindle_on);
    sys.rt_exec_state &= ~EXEC_FEED_HOLD;
    grbl.on_state_change(STATE_IDLE);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 1 && job_spindle_on);
    CHECK(job_motions[0].target.x == 1 && job_motions[0].target.y == -2);
    job_needle();
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_completions == 1 && !job_spindle_on);
    return 0;
}
