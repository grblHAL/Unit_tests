#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    char job[] = "/JOB.NC", directory[] = "/JOBS", missing[] = "/ABSENT.NC";
    sd_state = STATE_CYCLE;
    CHECK(sd_command("FD", job) == Status_SystemGClock);
    CHECK(sd_command("FMD", directory) == Status_SystemGClock);
    CHECK(sd_command("FRD", directory) == Status_SystemGClock);
    sd_state = STATE_IDLE;
    CHECK(sd_command("FD", missing) == Status_FileDeleteFailed);
    CHECK(sd_command("FRD", directory) == Status_FileDeleteFailed);
    CHECK(sd_command("FMD", directory) == Status_OK);
    CHECK(sd_command("FMD", directory) == Status_FileOpenFailed);
    fatfs_put_file("/JOBS/PART.NC", "G0", 2);
    CHECK(sd_command("FRD", directory) == Status_FileDeleteFailed);
    vfs_file_t *file = vfs_open(job, "r");
    CHECK(file);
    char bytes[9];
    CHECK(vfs_read(bytes, 1, sizeof(bytes), file) == sizeof(bytes));
    CHECK(!memcmp(bytes, "G1X1\nM30\n", sizeof(bytes)));
    vfs_close(file);
    return 0;
}
