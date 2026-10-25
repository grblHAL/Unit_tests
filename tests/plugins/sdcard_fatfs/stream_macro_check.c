#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    fatfs_put_file("/P100.macro", "M2\n", 3);
    sd_state = STATE_CHECK_MODE;
    CHECK(grbl.on_macro_execute(100, 0, (parameter_words_t){.$ = On}, 2) == Status_OK);
    CHECK(!fs_busy() && hal.stream.read == sd_serial_read);
    CHECK(grbl.on_macro_return == NULL);
    sd_state = STATE_IDLE;
    CHECK(grbl.on_macro_execute(100, 0, (parameter_words_t){.$ = On}, 1) == Status_Handled);
    CHECK(hal.stream.read() == 'M');
    grbl.on_macro_return();
    CHECK(!fs_busy());
    return 0;
}
