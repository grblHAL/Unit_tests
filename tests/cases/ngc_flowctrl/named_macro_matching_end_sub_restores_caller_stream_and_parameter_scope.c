#include "support/flow_static_macro_host.h"
#include "check.h"

int main(void)
{
    prepare_static_macro();
    CHECK(ngc_param_set(1, 99));
    CHECK(flow_command(static_macro_label, "CALL[12]") == Status_OK);
    execute_static_macro_file();
    CHECK(hal.stream.file == NULL);
    CHECK(hal.stream.read == stream_get_null);
    CHECK(ngc_call_level() == 0);
    float value;
    CHECK(ngc_param_get(1, &value));
    NEAR(value, 99);
    return EXIT_SUCCESS;
}
