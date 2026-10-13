#include "support/report_host.h"

int main(void)
{
    prepare_report();
    settings.flags.report_inches = true;
    report_init();
    sys.home_position[X_AXIS] = 25.4f;
    sys.home_position[Y_AXIS] = -50.8f;
    sys.home_position[Z_AXIS] = 76.2f;
    sys.homed.mask = X_AXIS_BIT | Z_AXIS_BIT;
    settings.homing.flags.enabled = true;
    report_ngc_parameters();
    CHECK(strstr(engine_output, "[HOME:1.0000,-2.0000,3.0000:5]" ASCII_EOL) != NULL);
    CHECK(sys.homed.mask == 5);
    return EXIT_SUCCESS;
}
