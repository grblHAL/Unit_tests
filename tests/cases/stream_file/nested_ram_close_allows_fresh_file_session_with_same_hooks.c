#include "support/nested_ram_stream_host.h"
int main(void)
{
    prepare_nested_ram_streams();
    close_nested_ram_level(2); close_nested_ram_level(1); close_nested_ram_level(0);
    nested_create_file("/ram/fresh", "F300\n");
    nested_ram_files[0] = stream_redirect_read("/ram/fresh", nested_status0, nested_eof0);
    CHECK(nested_ram_files[0] != NULL && stream_is_file());
    CHECK(grbl.on_line_number_assigned(0) == 0);
    nested_expect_text("F300\n");
    CHECK(grbl.on_line_number_assigned(0) == 1);
    CHECK(grbl.report.status_message(Status_UserException) == Status_OK && nested_status_calls[0] == 1);
    CHECK(hal.stream.read() == ASCII_EOF);
    CHECK(grbl.on_file_end(nested_ram_files[0], Status_OK) == Status_OK);
    CHECK(nested_eof_calls[0] == 1 && nested_prior_eof_calls == 1);
    close_nested_ram_level(0);
    return EXIT_SUCCESS;
}
