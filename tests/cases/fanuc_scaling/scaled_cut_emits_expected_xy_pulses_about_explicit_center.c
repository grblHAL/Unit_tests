#include "support/fanuc_scaling_host.h"
#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    CHECK(scaling_block("G51X1Y2P2") == Status_OK);
    queue_motion_program("G1X2Y3F100");
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 240 && axis_pulses[X_AXIS] == 240);
    CHECK(physical_position[Y_AXIS] == 320 && axis_pulses[Y_AXIS] == 320);
    CHECK(physical_position[Z_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 3);
    NEAR(gc_state.position[Y_AXIS], 4);
    return EXIT_SUCCESS;
}
