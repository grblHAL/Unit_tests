#include "support/file_stream_host.h"
int main(void)
{
    prepare_file_stream("G0X1\nG0X2\n");
    vfs_file_t *file = stream_redirect_read("/fixture/program", NULL, NULL);
    CHECK(file != NULL);
    stream_reposition(file, 5, 20);
    CHECK(vfs_tell(file) == 5);
    CHECK(grbl.on_line_number_assigned(0) == 20);
    CHECK(hal.stream.read() == 'G');
    CHECK(hal.stream.read() == '0');
    CHECK(hal.stream.read() == 'X');
    CHECK(hal.stream.read() == '2');
    CHECK(hal.stream.read() == ASCII_LF);
    CHECK(grbl.on_line_number_assigned(0) == 21);
    stream_redirect_close(file);
    return EXIT_SUCCESS;
}
