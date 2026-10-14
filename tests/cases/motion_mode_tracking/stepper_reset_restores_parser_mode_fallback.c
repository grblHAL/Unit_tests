#include "support/motion_mode_host.h"
int main(void)
{
    prepare_motion_modes();
    queue_motion_program("G0X1");
    queue_motion_program("G1X2F100");
    execute_motion_program();
    st_reset();
    CHECK(st_get_motion_mode() == gc_state.modal.motion);
    CHECK(st_get_motion_mode() == MotionMode_Linear);
    CHECK(sys.position[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
