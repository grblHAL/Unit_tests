#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    // A decimal radius just below half the chord differs only by float roundoff.
    queue_motion_program("G2X1Y0R0.49999997F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(sys.position[Y_AXIS] == 0 && physical_position[Y_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] > 0 && axis_pulses[Y_AXIS] <= 80);
    CHECK(axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
