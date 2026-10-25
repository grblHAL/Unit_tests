#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    CHECK(grbl.on_macro_execute(100, 0, (parameter_words_t){.$ = On}, 1) == Status_Unhandled);
    CHECK(!fs_busy() && grbl.on_macro_return == NULL);
    fatfs_put_file("/P100.macro", "M2\n", 3);
    CHECK(grbl.on_macro_execute(100, 0, (parameter_words_t){.$ = On}, 1) == Status_Handled);
    CHECK(hal.stream.read() == 'M');
    grbl.on_macro_return();
    CHECK(!fs_busy());
    return 0;
}
