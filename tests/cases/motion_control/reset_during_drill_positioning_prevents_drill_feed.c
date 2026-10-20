#include "support/drill_reset_motion_host.h"
int main(void)
{
    run_reset_drilling(Reset_Positioning);
    CHECK(physical_position[X_AXIS] >= 40 && physical_position[X_AXIS] < 80);
    CHECK(physical_position[Z_AXIS] == 160 && axis_pulses[Z_AXIS] == 160);
    return EXIT_SUCCESS;
}
