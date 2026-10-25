#include "job_host.h"
int main(void)
{
    job_break_sensor = true;
    job_prepare();
    CHECK(job_warnings == 0);
    uint8_t stitches[17 * 3] = {0};
    for (unsigned i = 0; i < 16; i++)
    {
        stitches[i * 3] = 1;
        stitches[i * 3 + 2] = 3;
    }
    stitches[16 * 3 + 2] = 0xf3;
    vfs_file_t *file = job_dst(stitches, sizeof(stitches));
    CHECK(grbl.on_file_open("job.dst", file, true) == Status_OK);
    for (unsigned i = 0; i < 7; i++)
        CHECK(hal.stream.read() == SERIAL_NO_DATA);
    job_break();
    job_run_tasks();
    CHECK(job_holds == 0);
    for (unsigned i = 0; i < 14; i++)
    {
        grbl.on_execute_realtime(STATE_IDLE);
        CHECK(job_motion_count == i + 1);
        job_needle();
        CHECK(hal.stream.read() == SERIAL_NO_DATA);
    }
    job_break();
    job_run_tasks();
    CHECK(job_holds == 1 && job_syncs == 1 && !job_spindle_on);
    CHECK(strstr(job_output, "Thread break!"));
    CHECK(job_motion_count == 15 && fabsf(job_motions[14].target.x - 1.4f) < .0001f);
    sys.rt_exec_state &= ~EXEC_FEED_HOLD;
    grbl.on_state_change(STATE_IDLE);
    for (unsigned i = 0; i < 2; i++)
    {
        grbl.on_execute_realtime(STATE_IDLE);
        job_needle();
    }
    CHECK(job_motion_count == 17 && fabsf(job_motions[16].target.x - 1.6f) < .0001f);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_completions == 1 && !job_spindle_on);
    return 0;
}
