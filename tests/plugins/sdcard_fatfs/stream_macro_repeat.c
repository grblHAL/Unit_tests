#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    fatfs_put_file("/P100.macro", "M2\n", 3);
    CHECK(grbl.on_macro_execute(100, 0, (parameter_words_t){.$ = On}, 3) == Status_Handled);
    for (unsigned repeat = 0; repeat < 3; repeat++) {
        CHECK(fs_busy());
        CHECK(hal.stream.read() == 'M');
        CHECK(hal.stream.read() == '2');
        CHECK(hal.stream.read() == ASCII_LF);
        CHECK(grbl.on_macro_return);
        grbl.on_macro_return();
    }
    CHECK(!fs_busy() && hal.stream.read == sd_serial_read);
    CHECK(grbl.on_macro_return == NULL);
    return 0;
}
