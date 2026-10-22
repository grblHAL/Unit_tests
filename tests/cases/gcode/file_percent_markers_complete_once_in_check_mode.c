#include "support/program_marker_file_host.h"

int main(void)
{
    prepare_marker_file(true);
    CHECK(program_block("%") == Status_OK);
    CHECK(HOST_PARSER_FLAGS.file_run && HOST_PARSER_FLAGS.file_stream);
    CHECK(file_marker_calls == 1 && last_file_marker);
    CHECK(program_complete_calls == 0);
    CHECK(program_block("%") == Status_OK);
    CHECK(!HOST_PARSER_FLAGS.file_run);
    CHECK(program_complete_calls == 1);
    CHECK(program_completion == ProgramFlow_EndPercent);
    CHECK(program_completion_check_mode == true);
    CHECK(file_marker_calls == 2 && !last_file_marker);
    stream_redirect_close(hal.stream.file);
    CHECK(file_closes == 1);
    return EXIT_SUCCESS;
}
