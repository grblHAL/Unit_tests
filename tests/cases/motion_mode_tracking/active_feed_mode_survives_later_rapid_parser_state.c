#include "support/motion_mode_host.h"
int main(void)
{
    prepare_motion_modes();
    queue_motion_program("G1X1F100");
    queue_motion_program("G0X2");
    CHECK(gc_state.modal.motion == MotionMode_Seek);
    execute_motion_program();
    CHECK(rapid_steps == 80 && feed_steps == 80);
    CHECK(mode_changes == 2);
    CHECK(mode_sequence[0] == MotionMode_Linear && mode_sequence[1] == MotionMode_Seek);
    CHECK(sys.position[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
