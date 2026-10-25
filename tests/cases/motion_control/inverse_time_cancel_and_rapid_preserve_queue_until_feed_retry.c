#include "support/motion_program_host.h"

int main(void)
{
    prepare_motion_program();
    char cancel[] = "G93G80";
    CHECK(gc_execute_block(cancel) == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime);
    CHECK(gc_state.modal.motion == MotionMode_None);
    CHECK(plan_get_current_block() == NULL);
    queue_motion_program("G0X1");
    plan_block_t *rapid = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    char cancelled_axes[] = "G80X2";
    CHECK(gc_execute_block(cancelled_axes) == Status_GcodeAxisWordsExist);
    CHECK(plan_get_current_block() == rapid);
    CHECK(plan_get_block_buffer_available() == available);
    CHECK(gc_state.modal.motion == MotionMode_Seek);
    char missing_feed[] = "G1X2";
    CHECK(gc_execute_block(missing_feed) == Status_GcodeUndefinedFeedRate);
    CHECK(plan_get_current_block() == rapid);
    CHECK(plan_get_block_buffer_available() == available);
    CHECK(gc_state.modal.motion == MotionMode_Seek);
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime);
    NEAR(gc_state.position[X_AXIS], 1);
    CHECK(axis_pulses[X_AXIS] == 0);
    queue_motion_program("G1X2F60");
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 160 && physical_position[X_AXIS] == 160);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 2);
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime);
    CHECK(sys.alarm == Alarm_None && !sys.abort);
    return EXIT_SUCCESS;
}
