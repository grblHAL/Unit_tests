#include "support/file_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_file_stream("G0X1");
    vfs_file_t *file = stream_redirect_read("/fixture/program", NULL, NULL);
    CHECK(file != NULL);
    CHECK(hal.stream.file == file);
    CHECK(hal.stream.read != stream_get_null);
    stream_redirect_close(file);
    CHECK(hal.stream.file == NULL);
    CHECK(hal.stream.read == stream_get_null);
    CHECK(file_closes == 1);
    return EXIT_SUCCESS;
}
