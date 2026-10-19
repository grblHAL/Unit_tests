#include "support/nested_ram_stream_host.h"
int main(void)
{
    prepare_nested_ram_streams();
    stream_read_ptr reader = hal.stream.read;
    size_t position = vfs_tell(hal.stream.file);
    CHECK(stream_redirect_read("/ram/missing", NULL, NULL) == NULL);
    CHECK(hal.stream.file == nested_ram_files[2] && hal.stream.read == reader);
    CHECK(vfs_tell(hal.stream.file) == position);
    CHECK(grbl.on_line_number_assigned(0) == 1);
    close_nested_ram_level(2);
    nested_expect_text("F200\n");
    close_nested_ram_level(1);
    nested_expect_text("G91\n");
    close_nested_ram_level(0);
    return EXIT_SUCCESS;
}
