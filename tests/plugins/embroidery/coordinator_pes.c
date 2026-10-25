#include "job_host.h"
int main(void)
{
    job_prepare();
    const uint8_t stitches[] = {10, 20, 0x76, 0x6c, 0xff};
    vfs_file_t *file = job_pes(stitches, sizeof(stitches));
    CHECK(grbl.on_file_open("job.pes", file, false) == Status_OK);
    CHECK(strstr(job_output, "G17G21G91") && strstr(job_output, "F4000"));
    CHECK(strstr(job_output, "T5 (MSG,"));
    CHECK(strstr(job_output, "G1X1Y-2") && strstr(job_output, "X-1Y2"));
    CHECK(strstr(job_output, "M30"));
    CHECK(embroidery_get_thread_color(5) != NULL);
    vfs_close(file);
    return 0;
}
