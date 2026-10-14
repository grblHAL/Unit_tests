#include "support/parameter_report_host.h"

int main(void)
{
    prepare_parameter_report();
    report_ngc_parameters();
    CHECK(parameter_hook_calls == 1 && parameter_status_calls == 0);
    const char *coordinate = strstr(engine_output, "[G54:");
    const char *probe = strstr(engine_output, "[PRB:");
    const char *plugin = strstr(engine_output, "[PLUGIN:ok]");
    CHECK(coordinate != NULL && probe != NULL && plugin != NULL);
    CHECK(coordinate < probe && probe < plugin);
    return EXIT_SUCCESS;
}
