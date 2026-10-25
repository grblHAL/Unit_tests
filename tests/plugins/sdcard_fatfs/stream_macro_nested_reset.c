#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    fatfs_put_file("/P100.macro", "AB\n", 3);
    fatfs_put_file("/P101.macro", "XY\n", 3);
    CHECK(grbl.on_macro_execute(100, 0, (parameter_words_t){.$ = On}, 2) == Status_Handled);
    CHECK(grbl.on_macro_execute(101, 0, (parameter_words_t){.$ = On}, 3) == Status_Handled);
    CHECK(hal.stream.read() == 'X');
    hal.driver_reset();
    CHECK(sd_resets == 1 && !fs_busy());
    CHECK(hal.stream.file == NULL && hal.stream.read == sd_serial_read);
    CHECK(grbl.on_macro_return == NULL);
    CHECK(grbl.on_macro_execute(100, 0, (parameter_words_t){.$ = On}, 1) == Status_Handled);
    CHECK(hal.stream.read() == 'A');
    grbl.on_macro_return();
    CHECK(!fs_busy());
    return 0;
}
