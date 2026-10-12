#include "support/file_stream_host.h"
#include "check.h"

int main(void)
{
    prepare_file_stream("X\r\nY");
    vfs_file_t *file = stream_redirect_read("/fixture/program", NULL, NULL);
    CHECK(file != NULL);
    CHECK(hal.stream.read() == 'X');
    CHECK(hal.stream.read() == ASCII_CR);
    CHECK(hal.stream.read() == SERIAL_NO_DATA);
    CHECK(grbl.on_line_number_assigned(0) == 1);
    CHECK(hal.stream.read() == 'Y');
    stream_redirect_close(file);
    return EXIT_SUCCESS;
}
