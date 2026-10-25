#include "file_stream_host.h"
int main(void)
{
    prepare_fatfs_job();
    fatfs_put_file("/P100.macro", "M2\n", 3);
    CHECK(grbl.on_macro_execute(100, 0, (parameter_words_t){.$ = On}, 2) == Status_Handled);
    CHECK(hal.stream.read() == 'M');
    CHECK(grbl.report.status_message(Status_GcodeValueOutOfRange) == Status_GcodeValueOutOfRange);
    CHECK(strstr(sd_output, "in macro P100.macro"));
    CHECK(sd_statuses == 1 && !fs_busy());
    CHECK(grbl.on_macro_return == NULL && hal.stream.read == sd_serial_read);
    CHECK(grbl.on_macro_execute(100, 0, (parameter_words_t){.$ = On}, 1) == Status_Handled);
    CHECK(hal.stream.read() == 'M');
    grbl.on_macro_return();
    CHECK(!fs_busy());
    return 0;
}
