#include "support/nested_ram_stream_host.h"
int main(void)
{
    prepare_ram_stream_environment();
    grbl.on_file_end = nested_previous_eof;
    nested_create_file("/ram/main", "G90\n");
    vfs_file_t *file = stream_redirect_read("/ram/main", NULL, NULL);
    CHECK(file != NULL);
    nested_expect_text("G90\n");
    CHECK(hal.stream.read() == ASCII_EOF);
    CHECK(grbl.on_file_end(file, Status_OK) == Status_OK);
    CHECK(nested_prior_eof_calls == 1 && nested_event_order == 1);
    stream_redirect_close(file);
    CHECK(!stream_is_file() && hal.stream.read == stream_get_null);
    return EXIT_SUCCESS;
}
