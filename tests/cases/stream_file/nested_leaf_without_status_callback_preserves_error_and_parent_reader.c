#include "support/nested_ram_stream_host.h"

int main(void)
{
    prepare_ram_stream_environment();
    nested_create_file("/ram/main", "G90\nG91\n");
    nested_create_file("/ram/leaf", "G21\n");
    nested_ram_files[0] = stream_redirect_read("/ram/main", nested_status0, NULL);
    CHECK(nested_ram_files[0] != NULL);
    nested_expect_text("G90\n");
    CHECK(grbl.on_line_number_assigned(0) == 1);
    vfs_file_t *leaf = stream_redirect_read("/ram/leaf", NULL, NULL);
    CHECK(leaf != NULL);
    stream_read_ptr reader = hal.stream.read;
    size_t position = vfs_tell(leaf);
    char invalid[] = "G999";
    status_code_t status = gc_execute_block(invalid);
    CHECK(status == Status_GcodeUnsupportedCommand);
    CHECK(grbl.report.status_message(status) == status);
    CHECK(gc_state.last_error == status && nested_status_calls[0] == 0);
    CHECK(hal.stream.file == leaf && hal.stream.read == reader && vfs_tell(leaf) == position);
    stream_redirect_close(leaf);
    CHECK(hal.stream.file == nested_ram_files[0] && hal.stream.read == reader);
    CHECK(grbl.on_line_number_assigned(0) == 1);
    CHECK(grbl.report.status_message(Status_UserException) == Status_OK);
    CHECK(nested_status_calls[0] == 1);
    nested_expect_text("G91\n");
    CHECK(grbl.on_line_number_assigned(0) == 2);
    stream_redirect_close(nested_ram_files[0]);
    CHECK(!stream_is_file() && hal.stream.read == stream_get_null);
    CHECK(grbl.report.status_message(Status_UserException) == Status_UserException);
    CHECK(nested_status_calls[0] == 1);
    return EXIT_SUCCESS;
}
