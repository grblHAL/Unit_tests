#include "support/file_stream_host.h"
static line_number_t expected_line, observed_line;
static unsigned observed_calls;
static line_number_t observe_assigned_line(line_number_t number)
{
    CHECK(number == expected_line);
    observed_line = number;
    observed_calls++;
    return number;
}
static void execute_file_line(void)
{
    char block[32];
    size_t used = 0;
    int32_t c;
    while((c = hal.stream.read()) != ASCII_LF) {
        CHECK(c >= 0 && c != ASCII_EOF && used + 1 < sizeof(block));
        block[used++] = (char)c;
    }
    block[used] = '\0';
    CHECK(gc_execute_block(block) == Status_OK);
}
int main(void)
{
    prepare_file_stream("G90\nN42G91\nG90\n");
    grbl.on_line_number_assigned = observe_assigned_line;
    vfs_file_t *file = stream_redirect_read("/fixture/program", NULL, NULL);
    CHECK(file != NULL);
    expected_line = 1;
    execute_file_line();
    CHECK(observed_calls > 0 && observed_line == 1);
    CHECK(gc_state.line_number == 1 && !gc_state.modal.distance_incremental);
    unsigned prior_calls = observed_calls;
    expected_line = 42;
    execute_file_line();
    CHECK(observed_calls > prior_calls && observed_line == 42);
    CHECK(gc_state.line_number == 42 && gc_state.modal.distance_incremental);
    prior_calls = observed_calls;
    expected_line = 43;
    execute_file_line();
    CHECK(observed_calls > prior_calls && observed_line == 43);
    CHECK(gc_state.line_number == 43 && !gc_state.modal.distance_incremental);
    CHECK(hal.stream.read() == ASCII_EOF);
    stream_redirect_close(file);
    CHECK(file_closes == 1 && !stream_is_file());
    prior_calls = observed_calls;
    expected_line = 77;
    char sender[] = "N77G90";
    CHECK(gc_execute_block(sender) == Status_OK);
    CHECK(observed_calls > prior_calls && observed_line == 77 && gc_state.line_number == 77);
    return EXIT_SUCCESS;
}
