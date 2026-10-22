#include "support/drill_reset_motion_host.h"
int main(void)
{
    run_reset_drilling(Reset_Retracting);
    CHECK(drilled_below_surface);
    CHECK(physical_position[Z_AXIS] >= 0 && physical_position[Z_AXIS] < 160);
    CHECK(physical_position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
