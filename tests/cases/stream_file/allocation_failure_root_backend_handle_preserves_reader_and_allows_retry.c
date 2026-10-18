#include "support/file_stream_allocation_host.h"
int main(void)
{
    prepare_file_heap();
    reject_file_open(1, "/embedded/child");
    CHECK(hal.stream.file == NULL && hal.stream.read == stream_get_null && !stream_is_file());
    vfs_file_t *child = stream_redirect_read("/embedded/child", NULL, NULL);
    CHECK(child != NULL);
    nested_expect_text("F100\n");
    stream_redirect_close(child);
    CHECK(!stream_is_file() && hal.stream.read == stream_get_null);
    return EXIT_SUCCESS;
}
