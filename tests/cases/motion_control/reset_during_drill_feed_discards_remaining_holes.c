#include "support/drill_reset_motion_host.h"
int main(void)
{
    run_reset_drilling(Reset_Drilling);
    CHECK(physical_position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    CHECK(physical_position[Z_AXIS] <= -20 && physical_position[Z_AXIS] > -240);
    return EXIT_SUCCESS;
}
