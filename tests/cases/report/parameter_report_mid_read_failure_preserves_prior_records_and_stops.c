#include "support/parameter_report_host.h"

int main(void)
{
    prepare_parameter_report(); parameter_fail_read = 3;
    report_ngc_parameters();
    CHECK(parameter_status_calls == 1 && parameter_status == Status_SettingReadFail);
    CHECK(parameter_read_calls == 3 && parameter_hook_calls == 0);
    CHECK(strstr(engine_output, "[G54:") != NULL && strstr(engine_output, "[G55:") != NULL);
    CHECK(strstr(engine_output, "[G56:") == NULL && strstr(engine_output, "[PRB:") == NULL);
    return EXIT_SUCCESS;
}
