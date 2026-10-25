#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    CHECK(grbl.on_macro_execute(99, 0, (parameter_words_t){0}, 1) == Status_Unhandled);
    CHECK(!fs_busy() && hal.stream.read == sd_serial_read);
    CHECK(grbl.on_macro_return == NULL);
    return 0;
}
