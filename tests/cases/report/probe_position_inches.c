#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    settings.flags.report_inches = true;
    report_init();
    sys.probe_position[X_AXIS] = 2032;
    sys.flags.probe_succeeded = true;
    report_probe_parameters();
    CHECK(strcmp(engine_output, "[PRB:1.0000,0.0000,0.0000:1]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
