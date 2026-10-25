#include "job_host.h"
int main(void)
{
    job_prepare();
    job_sync(false);
    uint8_t stitches[19 * 3] = {0};
    for (unsigned i = 0; i < 18; i++)
    {
        stitches[i * 3] = 1;
        stitches[i * 3 + 2] = 3;
    }
    stitches[18 * 3 + 2] = 0xf3;
    vfs_file_t *file = job_dst(stitches, sizeof(stitches));
    CHECK(grbl.on_file_open("job.dst", file, true) == Status_OK);
    // The eight-slot queue holds seven entries; repeated reads while full must retain later
    // stitches.
    for (unsigned i = 0; i < 20; i++)
        CHECK(hal.stream.read() == SERIAL_NO_DATA);
    CHECK(job_motion_count == 0);
    for (unsigned i = 0; i < 18; i++)
    {
        grbl.on_execute_realtime(STATE_IDLE);
        CHECK(job_motion_count == (i + 1) * 3);
        CHECK(fabsf(job_motions[i * 3].target.x - (i + 1) * .1f) < .0001f);
        CHECK(job_motions[i * 3].target.y == 0);
        CHECK(job_motions[i * 3 + 1].target.z == -10);
        CHECK(job_motions[i * 3 + 2].target.z == 10);
        CHECK(hal.stream.read() == SERIAL_NO_DATA);
    }
    grbl.on_execute_realtime(STATE_IDLE);
    CHECK(job_completions == 1 && job_motion_count == 54 && job_cancels == 1);
    CHECK(hal.stream.read == job_serial_read);
    return 0;
}
