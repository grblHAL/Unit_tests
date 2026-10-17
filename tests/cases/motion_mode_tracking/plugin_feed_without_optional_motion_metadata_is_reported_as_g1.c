#include "support/motion_mode_host.h"
int main(void)
{
    prepare_motion_modes();
    CHECK(gc_state.modal.motion == MotionMode_Seek);
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    float target[N_AXIS] = {1};
    CHECK(mc_line(target, &data) == Status_Handled);
    CHECK(plan_get_current_block()->motion_mode == MotionMode_Linear);
    execute_motion_program();
    CHECK(feed_steps == 80 && rapid_steps == 0);
    CHECK(strncmp(feed_report, "[GC:G1 ", 7) == 0);
    CHECK(physical_position[X_AXIS] == 80);
    CHECK(gc_state.modal.motion == MotionMode_Seek);
    return EXIT_SUCCESS;
}
