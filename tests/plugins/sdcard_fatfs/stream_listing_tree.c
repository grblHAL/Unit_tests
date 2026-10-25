#include "file_stream_host.h"
int main(void)
{
    sd_prepare(true);
    CHECK(vfs_mkdir("/JOBS") == 0);
    fatfs_put_file("/JOBS/PART.NC", "G0", 2);
    fatfs_put_file("/JOBS/NOTES.BIN", "note", 4);
    settings.fs_options.hierarchical_listing = false;
    CHECK(sd_command("F", NULL) == Status_OK);
    CHECK(strstr(sd_output, "JOBS/PART.NC|SIZE:2"));
    CHECK(!strstr(sd_output, "NOTES.BIN"));
    sd_clear_output();
    CHECK(sd_command("F+", NULL) == Status_OK);
    CHECK(strstr(sd_output, "JOBS/NOTES.BIN|SIZE:4"));
    sd_clear_output();
    settings.fs_options.hierarchical_listing = true;
    CHECK(sd_command("F", NULL) == Status_OK);
    CHECK(strstr(sd_output, "JOBS|SIZE:-1"));
    CHECK(!strstr(sd_output, "PART.NC"));
    return 0;
}
