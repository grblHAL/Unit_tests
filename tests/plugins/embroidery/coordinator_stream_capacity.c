#include "job_host.h"
int main(void)
{
    job_prepare();
    job_sync(false);
    const uint8_t stitches[] = {1, 0, 3, 0, 0, 0xf3};
    vfs_file_t *file = job_dst(stitches, sizeof(stitches));
    CHECK(grbl.on_file_open("job.dst", file, true) == Status_OK);
    CHECK(hal.stream.read() == SERIAL_NO_DATA);
    CHECK(hal.stream.read() == SERIAL_NO_DATA);
    job_planner_free = 2;
    for (unsigned i = 0; i < 4; i++)
        grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 0 && job_completions == 0);
    job_planner_free = 3;
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 3 && fabsf(job_motions[0].target.x - .1f) < .0001f);
    hal.driver_reset();
    CHECK(job_resets == 1 && job_completions == 0);
    CHECK(hal.stream.file == NULL && hal.stream.read == job_serial_read);
    CHECK(!job_spindle_on);
    return 0;
}
