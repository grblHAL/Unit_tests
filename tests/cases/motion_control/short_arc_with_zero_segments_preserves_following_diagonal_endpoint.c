#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    // Five degrees on a 1mm radius rounds to zero intermediate segments.
    queue_motion_program("G2X0.0038053Y0.0871557I1F100");
    CHECK(plan_get_current_block()->steps.value[X_AXIS] == 0);
    CHECK(plan_get_current_block()->steps.value[Y_AXIS] == 7);
    queue_motion_program("G1X1Y1F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 80 && sys.position[Y_AXIS] == 80);
    CHECK(physical_position[X_AXIS] == 80 && physical_position[Y_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80 && axis_pulses[Y_AXIS] == 80);
    CHECK(axis_pulses[Z_AXIS] == 0);
    CHECK(fabsf(gc_state.position[X_AXIS] - 1.0f) < 0.00001f);
    CHECK(fabsf(gc_state.position[Y_AXIS] - 1.0f) < 0.00001f);
    return EXIT_SUCCESS;
}
