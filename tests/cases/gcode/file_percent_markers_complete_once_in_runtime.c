#include "support/program_marker_file_host.h"

int main(void)
{
    prepare_marker_file(false);
    CHECK(program_block("%") == Status_OK);
    CHECK(gc_state.file_run && gc_state.file_stream);
    CHECK(file_marker_calls == 1 && last_file_marker);
    CHECK(program_complete_calls == 0);
    CHECK(program_block("%") == Status_OK);
    CHECK(!gc_state.file_run);
    CHECK(program_complete_calls == 1);
    CHECK(program_completion == ProgramFlow_EndPercent);
    CHECK(program_completion_check_mode == false);
    CHECK(file_marker_calls == 2 && !last_file_marker);
    if(hal.stream.file) stream_redirect_close(hal.stream.file);
    CHECK(file_closes == 1);
    return EXIT_SUCCESS;
}
