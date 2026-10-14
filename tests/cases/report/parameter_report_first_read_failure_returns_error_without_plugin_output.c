#include "support/parameter_report_host.h"

int main(void)
{
    prepare_parameter_report(); parameter_fail_read = 1;
    report_ngc_parameters();
    CHECK(parameter_status_calls == 1 && parameter_status == Status_SettingReadFail);
    CHECK(parameter_read_calls == 1 && parameter_hook_calls == 0);
    CHECK(engine_output[0] == 0);
    return EXIT_SUCCESS;
}
