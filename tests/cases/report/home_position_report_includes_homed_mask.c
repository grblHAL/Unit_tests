#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    settings.homing.flags.enabled = true;
    sys.home_position[X_AXIS] = 1;
    sys.home_position[Y_AXIS] = -2;
    sys.home_position[Z_AXIS] = 3;
    sys.homed.mask = 5;
    report_ngc_parameters();
    CHECK(strstr(engine_output, "[HOME:1.000,-2.000,3.000:5]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
