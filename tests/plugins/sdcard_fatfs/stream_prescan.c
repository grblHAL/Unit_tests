#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    settings.flags.m98_prescan_enable = true;
    char name[] = "/JOB.NC";
    CHECK(stream_file(STATE_IDLE, name) == Status_OK);
    CHECK(sd_state == STATE_CHECK_MODE);
    for (unsigned i = 0; i < 9; i++) CHECK(hal.stream.read() != SERIAL_NO_DATA);
    grbl.on_program_completed(ProgramFlow_CompletedM30, true);
    CHECK(hal.stream.state.m98_macro_prescan);
    // Rewinding clears the EOL state, so the stream supplies a separator first.
    CHECK(hal.stream.read() == ASCII_LF);
    CHECK(sd_state == STATE_IDLE && !hal.stream.state.m98_macro_prescan);
    CHECK(fs_busy() && stream_get_job_info()->pos == 0);
    CHECK(hal.stream.read() == 'G');
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(!fs_busy());
    return 0;
}
