#include "support/file_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_file_stream("G0X1");
    vfs_file_t *file = stream_redirect_read("/fixture/program", NULL, NULL);
    CHECK(file != NULL);
    CHECK(hal.stream.read() == 'G');
    CHECK(hal.stream.read() == '0');
    CHECK(hal.stream.read() == 'X');
    CHECK(hal.stream.read() == '1');
    CHECK(hal.stream.read() == ASCII_LF);
    CHECK(hal.stream.read() == ASCII_EOF);
    stream_redirect_close(file);
    return EXIT_SUCCESS;
}
