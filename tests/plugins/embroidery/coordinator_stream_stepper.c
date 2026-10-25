#include "job_host.h"
int main(void)
{
    job_prepare();
    job_sync(false);
    const uint8_t stitches[] = {0x85, 0x81, 0x03, 0x4a, 0x42, 0x03, 0, 0, 0xf3};
    vfs_file_t *file = job_dst(stitches, sizeof(stitches));
    CHECK(grbl.on_file_open("job.dst", file, true) == Status_OK);
    for (unsigned i = 0; i < 3; i++)
        CHECK(hal.stream.read() == SERIAL_NO_DATA);
    CHECK(job_motion_count == 0);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 3);
    CHECK(fabsf(job_motions[0].target.x - 1.3f) < .0001f);
    CHECK(fabsf(job_motions[0].target.y - .4f) < .0001f);
    CHECK(job_motions[1].target.z == -10 && job_motions[2].target.z == 10);
    CHECK(job_motions[0].feed == 4000 && !job_motions[0].rapid);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_motion_count == 6);
    CHECK(fabsf(job_motions[3].target.x) < .0001f && fabsf(job_motions[3].target.y) < .0001f);
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_completions == 1 && job_feedback == 1 && job_cancels == 1);
    CHECK(hal.stream.file == NULL && hal.stream.read == job_serial_read);
    CHECK(!job_spindle_on);
    return 0;
}
