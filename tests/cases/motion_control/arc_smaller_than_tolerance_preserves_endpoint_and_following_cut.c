#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    // Diameter equals the configured 0.02mm tolerance: use the endpoint chord.
    queue_motion_program("G2X0.02I0.01F100");
    CHECK(plan_get_current_block()->steps.value[X_AXIS] == 2);
    CHECK(plan_get_current_block()->steps.value[Y_AXIS] == 0);
    queue_motion_program("G1X1F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(sys.position[Y_AXIS] == 0 && sys.position[Z_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(fabsf(gc_state.position[X_AXIS] - 1.0f) < 0.00001f);
    return EXIT_SUCCESS;
}
