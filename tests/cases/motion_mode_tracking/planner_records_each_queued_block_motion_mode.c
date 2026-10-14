#include "support/motion_mode_host.h"
int main(void)
{
    prepare_motion_modes();
    queue_motion_program("G0X1");
    CHECK(plan_get_current_block()->motion_mode == MotionMode_Seek);
    queue_motion_program("G1X2F100");
    CHECK(gc_state.modal.motion == MotionMode_Linear);
    CHECK(plan_get_current_block()->motion_mode == MotionMode_Seek);
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
