#include "sd_host.h"
int main(void)
{
    sd_prepare(true);
    CHECK(grbl.on_macro_execute(100, 0, (parameter_words_t){.$ = On}, 2) == Status_Handled);
    CHECK(fs_busy());
    CHECK(hal.stream.read() == 'M');
    CHECK(hal.stream.read() == '2');
    CHECK(hal.stream.read() == ASCII_LF);
    CHECK(grbl.on_macro_return);
    grbl.on_macro_return();
    CHECK(hal.stream.read() == 'M');
    grbl.on_macro_return();
    CHECK(!fs_busy() && hal.stream.read == sd_serial_read);
    return 0;
}
