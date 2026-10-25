#include "job_host.h"
int main(void)
{
    job_prepare();
    job_delay(250);
    const uint8_t stitches[] = {1, 1, 1, 1, 0xa0, 0, 0xa0, 0, 0xff};
    vfs_file_t *file = job_pes(stitches, sizeof(stitches));
    CHECK(grbl.on_file_open("job.pes", file, true) == Status_OK);
    for (unsigned i = 0; i < 5; i++)
        CHECK(hal.stream.read() == SERIAL_NO_DATA);
    grbl.on_execute_realtime(STATE_IDLE);
    job_run_tasks();
    sys.rt_exec_state &= ~EXEC_FEED_HOLD;
    grbl.on_state_change(STATE_IDLE);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 1 && job_spindle_on);
    job_needle();
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 2 && job_spindle_on);
    job_advance(249);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_spindle_on && job_motion_count == 2);
    job_advance(1);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(!job_spindle_on && job_motion_count == 2);
    job_needle();
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 3 && job_motions[2].rapid);
    job_run_tasks();
    hal.driver_reset();
    CHECK(job_resets == 1 && !job_spindle_on && hal.stream.read == job_serial_read);
    return 0;
}
