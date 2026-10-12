#include "support/flow_static_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_static_macro();
    CHECK(ngc_param_set(1, 99));
    CHECK(flow_command(static_macro_label, "CALL[12][34]") == Status_OK);
    CHECK(hal.stream.file != NULL);
    CHECK(ngc_call_level() == 1);
    float value;
    CHECK(ngc_param_get(1, &value));
    NEAR(value, 12);
    CHECK(ngc_param_get(2, &value));
    NEAR(value, 34);
    vfs_file_t *file = hal.stream.file;
    CHECK(grbl.on_file_end(file, Status_OK) == Status_OK);
    CHECK(hal.stream.file == NULL);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
