#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    sys.probe_position[X_AXIS] = 80;
    sys.probe_position[Y_AXIS] = -160;
    sys.probe_position[Z_AXIS] = 240;
    sys.flags.probe_succeeded = true;
    report_probe_parameters();
    CHECK(strcmp(engine_output, "[PRB:1.000,-2.000,3.000:1]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
