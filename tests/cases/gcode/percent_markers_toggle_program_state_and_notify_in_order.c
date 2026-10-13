#include "support/program_end_host.h"
static unsigned marker_calls;
static bool marker_start[2];
static void demarcated(bool start) { CHECK(marker_calls < 2); marker_start[marker_calls++] = start; }

int main(void)
{
    prepare_program_end(true);
    grbl.on_file_demarcate = demarcated;
    CHECK(program_block("%") == Status_OK);
    CHECK(gc_get_state()->file_run);
    CHECK(marker_calls == 1 && marker_start[0]);
    CHECK(program_complete_calls == 0);
    CHECK(program_block("%") == Status_OK);
    CHECK(!gc_get_state()->file_run);
    CHECK(marker_calls == 2 && !marker_start[1]);
    CHECK(program_complete_calls == 0);
    return EXIT_SUCCESS;
}
