#include "job_host.h"
int main(void)
{
    job_prepare();
    const uint8_t stitches[] = {0x85, 0x81, 0x03, 0x4a, 0x42, 0x03, 0, 0, 0xf3};
    vfs_file_t *file = job_dst(stitches, sizeof(stitches));
    CHECK(grbl.on_file_open("job.dst", file, false) == Status_OK);
    CHECK(strstr(job_output, "G17G21G91") && strstr(job_output, "F4000"));
    CHECK(strstr(job_output, "G1X1.3Y0.4") && strstr(job_output, "X-1.3Y-0.4"));
    CHECK(strstr(job_output, "M30"));
    CHECK(hal.stream.type == StreamType_Serial);
    vfs_close(file);
    hal.driver_reset();
    CHECK(job_resets == 1);
    return 0;
}
