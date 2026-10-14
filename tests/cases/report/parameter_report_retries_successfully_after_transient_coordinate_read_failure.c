#include "support/parameter_report_host.h"

int main(void)
{
    prepare_parameter_report(); parameter_fail_read = 1;
    report_ngc_parameters(); CHECK(parameter_status_calls == 1 && parameter_hook_calls == 0);
    engine_output[0] = 0;
    report_ngc_parameters();
    CHECK(parameter_status_calls == 1 && parameter_hook_calls == 1);
    CHECK(strstr(engine_output, "[G54:0.000,0.000,0.000]") != NULL);
    CHECK(strstr(engine_output, "[PRB:") != NULL && strstr(engine_output, "[PLUGIN:ok]") != NULL);
    return EXIT_SUCCESS;
}
