#include "support/program_marker_file_host.h"

int main(void)
{
    prepare_marker_file(false);
    CHECK(program_block("G21") == Status_OK);
    CHECK(gc_state.file_stream && !gc_state.file_run);
    CHECK(program_block("%") == Status_UnexpectedDemarcation);
    CHECK(program_complete_calls == 0 && file_marker_calls == 0);
    stream_redirect_close(hal.stream.file);
    CHECK(file_closes == 1);
    return EXIT_SUCCESS;
}
