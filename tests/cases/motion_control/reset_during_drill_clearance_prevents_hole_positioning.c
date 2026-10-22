#include "support/drill_reset_motion_host.h"
int main(void)
{
    run_reset_drilling(Reset_Clearance);
    CHECK(physical_position[Z_AXIS] >= 40 && physical_position[Z_AXIS] < 160);
    CHECK(axis_pulses[X_AXIS] == 0);
    return EXIT_SUCCESS;
}
