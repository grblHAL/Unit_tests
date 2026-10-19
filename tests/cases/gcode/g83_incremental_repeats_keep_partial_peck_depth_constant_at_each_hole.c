#include "support/partial_peck_motion_host.h"
int main(void)
{
    prepare_partial_peck_motion();
    execute_canned("G91G99G83X1Z-1.25R0Q0.5L3F100");
    CHECK(partial_peck_deepest_z == -100);
    CHECK(physical_position[Z_AXIS] == 0 && sys.position[Z_AXIS] == 0);
    CHECK(axis_pulses[Z_AXIS] == 1320);
    CHECK(physical_position[X_AXIS] == 240 && axis_pulses[X_AXIS] == 240);
    CHECK(axis_pulses[Y_AXIS] == 0);
    return EXIT_SUCCESS;
}
