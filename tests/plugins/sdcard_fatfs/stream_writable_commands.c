#include "file_stream_host.h"
int main(void)
{
    sd_prepare(true);
    char directory[] = "/JOBS";
    CHECK(sd_command("FMD", directory) == Status_OK);
    fatfs_put_file("/JOBS/PART.NC", "G0", 2);
    char file[] = "/JOBS/PART.NC";
    CHECK(sd_command("FD", file) == Status_OK);
    CHECK(!vfs_open("/JOBS/PART.NC", "r"));
    CHECK(sd_command("FRD", directory) == Status_OK && !vfs_opendir("/JOBS"));
    return 0;
}
