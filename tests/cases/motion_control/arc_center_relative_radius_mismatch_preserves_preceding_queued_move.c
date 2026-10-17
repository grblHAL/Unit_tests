#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G1X1F100");
    /* 0.1 mm is below the gross 0.5 mm threshold but above 0.1% of 10 mm. */
    char invalid_arc[] = "G3X11Y10.1I10";
    CHECK(gc_execute_block(invalid_arc) == Status_GcodeInvalidTarget);
    CHECK(gc_state.modal.motion == MotionMode_Linear);
    NEAR(gc_state.position[X_AXIS], 1);
    NEAR(gc_state.position[Y_AXIS], 0);
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 80 && sys.position[X_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
