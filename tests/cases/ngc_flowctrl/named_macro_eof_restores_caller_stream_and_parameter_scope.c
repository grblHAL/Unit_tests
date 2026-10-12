#include "support/flow_static_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_static_macro();
    CHECK(ngc_param_set(1, 99));
    CHECK(flow_command(static_macro_label, "CALL[12]") == Status_OK);
    vfs_file_t *file = hal.stream.file;
    CHECK(hal.stream.read() == 'G');
    CHECK(hal.stream.read() == '2');
    CHECK(hal.stream.read() == '1');
    CHECK(hal.stream.read() == ASCII_LF);
    CHECK(hal.stream.read() == ASCII_EOF);
    CHECK(grbl.on_file_end(file, Status_OK) == Status_OK);
    CHECK(hal.stream.file == NULL);
    CHECK(hal.stream.read == stream_get_null);
    CHECK(ngc_call_level() == 0);
    float value;
    CHECK(ngc_param_get(1, &value));
    NEAR(value, 99);
    return EXIT_SUCCESS;
}
