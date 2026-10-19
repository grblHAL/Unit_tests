#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G93G0X2");
    execute_motion_program();
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime);
    CHECK(physical_position[X_AXIS] == 160 && axis_pulses[X_AXIS] == 160);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
