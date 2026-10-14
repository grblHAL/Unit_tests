#include "support/motion_mode_host.h"
int main(void)
{
    prepare_motion_modes();
    queue_motion_program("G3X1Y1I0J1F100");
    queue_motion_program("G1X2Y1F100");
    execute_motion_program();
    CHECK(mode_changes == 2);
    CHECK(mode_sequence[0] == MotionMode_CcwArc && mode_sequence[1] == MotionMode_Linear);
    CHECK(sys.position[X_AXIS] == 160 && sys.position[Y_AXIS] == 80);
    CHECK(rapid_steps == 0 && feed_steps > 0);
    return EXIT_SUCCESS;
}
