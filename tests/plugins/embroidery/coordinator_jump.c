#include "job_host.h"
int main(void)
{
    job_prepare();
    const uint8_t stitches[] = {1, 0, 0x83, 1, 0, 3, 0, 0, 0xf3};
    vfs_file_t *file = job_dst(stitches, sizeof(stitches));
    CHECK(grbl.on_file_open("job.dst", file, false) == Status_OK);
    CHECK(strstr(job_output, "G0X0.1"));
    CHECK(strstr(job_output, "G1X0.1"));
    CHECK(strstr(job_output, "M30"));
    vfs_close(file);
    return 0;
}
