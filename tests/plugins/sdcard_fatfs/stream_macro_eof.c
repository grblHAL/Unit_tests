#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    fatfs_put_file("/P100.macro", "M2\n", 3);
    CHECK(grbl.on_macro_execute(100, 0, (parameter_words_t){.$ = On}, 2) == Status_Handled);
    for (unsigned repeat = 0; repeat < 2; repeat++) {
        CHECK(hal.stream.read() == 'M');
        CHECK(hal.stream.read() == '2');
        CHECK(hal.stream.read() == ASCII_LF);
        CHECK(hal.stream.read() == ASCII_EOF);
        // protocol.c signals this public event after consuming ASCII_EOF.
        CHECK(grbl.on_file_end(hal.stream.file, Status_OK) == Status_OK);
        CHECK(sd_statuses == repeat);
    }
    CHECK(!fs_busy() && hal.stream.read == sd_serial_read);
    CHECK(grbl.on_macro_return == NULL);
    return 0;
}
