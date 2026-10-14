#include "support/motion_mode_host.h"
int main(void)
{
    prepare_motion_modes();
    queue_motion_program("G0X1");
    queue_motion_program("G1X2F100");
    CHECK(gc_state.modal.motion == MotionMode_Linear);
    execute_motion_program();
    CHECK(rapid_steps == 80 && feed_steps == 80);
    CHECK(mode_changes == 2);
    CHECK(mode_sequence[0] == MotionMode_Seek && mode_sequence[1] == MotionMode_Linear);
    CHECK(sys.position[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
