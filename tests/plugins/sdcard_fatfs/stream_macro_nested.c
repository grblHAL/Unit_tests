#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    fatfs_put_file("/P100.macro", "AB\n", 3);
    fatfs_put_file("/P101.macro", "XY\n", 3);
    CHECK(grbl.on_macro_execute(100, 0, (parameter_words_t){.$ = On}, 1) == Status_Handled);
    CHECK(hal.stream.read() == 'A');
    vfs_file_t *parent = hal.stream.file;
    CHECK(grbl.on_macro_execute(101, 0, (parameter_words_t){.$ = On}, 1) == Status_Handled);
    CHECK(hal.stream.file != parent && hal.stream.read() == 'X');
    grbl.on_macro_return();
    CHECK(fs_busy() && hal.stream.file == parent);
    CHECK(hal.stream.read() == 'B');
    grbl.on_macro_return();
    CHECK(!fs_busy() && hal.stream.read == sd_serial_read);
    CHECK(grbl.on_macro_return == NULL);
    return 0;
}
