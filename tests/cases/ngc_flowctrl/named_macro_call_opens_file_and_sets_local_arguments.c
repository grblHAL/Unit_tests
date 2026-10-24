#include "support/flow_static_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_static_macro();
    CHECK(ngc_param_set(1, 99));
    CHECK(flow_command(static_macro_label, "CALL[12][34]") == Status_OK);
    CHECK(hal.stream.file != NULL);
    CHECK(ngc_call_level() == 1);
    CHECK(flow_command(static_macro_label, "SUB") == Status_OK);
    CHECK(flow_command(static_macro_label, "ENDSUB") == Status_OK);
    CHECK(flow_command(static_macro_label, "SUB") == Status_OK);
    CHECK(!gc_state.skip_blocks);
    float value;
    CHECK(ngc_param_get(1, &value));
    NEAR(value, 12);
    CHECK(ngc_param_get(2, &value));
    NEAR(value, 34);
    vfs_file_t *file = hal.stream.file;
    status_code_t eof_status = grbl.on_file_end(file, Status_OK);
    CHECK(eof_status == Status_OK || eof_status == Status_Handled);
    CHECK(hal.stream.file == NULL);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
