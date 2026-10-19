#include "support/partial_peck_motion_host.h"
int main(void)
{
    prepare_partial_peck_motion();
    execute_canned("G0Z1");
    axis_pulses[Z_AXIS] = 0;
    execute_canned("G98G83X1Z-1.25R0Q0.5F100");
    CHECK(partial_peck_deepest_z == -100);
    CHECK(physical_position[Z_AXIS] == 80 && sys.position[Z_AXIS] == 80);
    CHECK(axis_pulses[Z_AXIS] > 440);
    NEAR(gc_state.position[Z_AXIS], 1);
    CHECK(physical_position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
