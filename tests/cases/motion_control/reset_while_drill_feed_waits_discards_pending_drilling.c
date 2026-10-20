#include "support/drill_reset_motion_host.h"
int main(void)
{
    drill_prefill_motion = true;
    drill_planner_slots_to_leave = 1;
    run_reset_drilling_program(Reset_Positioning, "G91G81X1Z-5R0L2F100");
    CHECK(physical_position[X_AXIS] >= 40 && physical_position[X_AXIS] < 80);
    CHECK(axis_pulses[Z_AXIS] == 0 && physical_position[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
