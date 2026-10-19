#include "support/file_stream_allocation_host.h"
int main(void)
{
    prepare_file_heap();
    vfs_file_t *parent = stream_redirect_read("/embedded/parent", NULL, NULL);
    CHECK(parent != NULL);
    nested_expect_text("G90\n");
    CHECK(grbl.on_line_number_assigned(0) == 1);
    stream_read_ptr reader = hal.stream.read;
    reject_file_open(2, "/embedded/child");
    CHECK(hal.stream.file == parent && hal.stream.read == reader && stream_is_file());
    CHECK(grbl.on_line_number_assigned(0) == 1);
    vfs_file_t *child = stream_redirect_read("/embedded/child", NULL, NULL);
    CHECK(child != NULL);
    nested_expect_text("F100\n");
    stream_redirect_close(child);
    CHECK(hal.stream.file == parent && hal.stream.read == reader);
    CHECK(grbl.on_line_number_assigned(0) == 1);
    nested_expect_text("G91\n");
    stream_redirect_close(parent);
    CHECK(!stream_is_file() && hal.stream.read == stream_get_null);
    return EXIT_SUCCESS;
}
