#include "file_stream_host.h"
int main(void)
{
    sd_prepare(true);
    CHECK(vfs_mkdir("/JOBS") == 0);
    fatfs_put_file("/JOBS/PART.NC", "G0", 2);
    char directory[] = "/JOBS";
    CHECK(stream_file(STATE_IDLE, directory) == Status_OK);
    CHECK(!fs_busy());
    sd_clear_output();
    CHECK(sd_command("PWD", NULL) == Status_OK);
    CHECK(strstr(sd_output, "[CWD:/JOBS]"));
    char missing[] = "/ABSENT";
    CHECK(sd_command("CWD", missing) == Status_FSDirNotFound);
    char part[] = "PART.NC";
    CHECK(sd_command("F", part) == Status_OK && hal.stream.read() == 'G');
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(!fs_busy());
    return 0;
}
