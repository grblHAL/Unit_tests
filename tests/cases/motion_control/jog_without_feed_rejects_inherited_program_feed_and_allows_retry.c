#include "support/jog_motion_host.h"
int main(void)
{
    prepare_jog_motion();
    char program_feed[] = "G90G1F120";
    CHECK(gc_execute_block(program_feed) == Status_OK);
    CHECK(system_command("$J=G91X1") == Status_GcodeUndefinedFeedRate);
    CHECK(state_get() == STATE_IDLE && wake_calls == 0);
    CHECK(plan_get_current_block() == NULL && !sys.abort);
    NEAR(gc_state.feed_rate, 120);
    CHECK(gc_state.modal.distance_incremental == false);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == 0 && physical_position[axis] == 0);
        CHECK(axis_pulses[axis] == 0);
    }
    CHECK(system_command("$J=G91X1F100") == Status_OK);
    finish_jog_motion();
    CHECK(physical_position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    NEAR(gc_state.feed_rate, 120);
    CHECK(gc_state.modal.distance_incremental == false);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
