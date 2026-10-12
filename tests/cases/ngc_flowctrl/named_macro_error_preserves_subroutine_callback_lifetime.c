#include "support/flow_static_macro_host.h"
#include "check.h"
int main(void)
{
    prepare_static_macro();
    CHECK(ngc_param_set(1, 99));
    CHECK(flow_command(static_macro_label, "CALL[12]") == Status_OK);
    CHECK(grbl.report.status_message(Status_GcodeUnsupportedCommand) == Status_GcodeUnsupportedCommand);
    CHECK(file_closes == 1);
    CHECK(hal.stream.file == NULL);
    CHECK(ngc_call_level() == 0);
    float value;
    CHECK(ngc_param_get(1, &value));
    NEAR(value, 99);
    return EXIT_SUCCESS;
}
