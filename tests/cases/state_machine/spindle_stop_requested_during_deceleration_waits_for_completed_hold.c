#include "support/hold_spindle_host.h"
int main(void)
{
    start_spindle_move(true);
    CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    CHECK(protocol_exec_rt_system());
    CHECK(sys.holding_state == Hold_Pending);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_STOP));
    CHECK(protocol_exec_rt_system());
    state_suspend_manager();
    CHECK(hold_spindle_output_state.on);
    CHECK(sys.override.spindle_stop.initiate);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(sys.holding_state == Hold_Complete);
    unsigned pulses = axis_pulses[X_AXIS];
    state_suspend_manager();
    CHECK(!hold_spindle_output_state.on);
    CHECK(sys.override.spindle_stop.enabled);
    CHECK(axis_pulses[X_AXIS] == pulses);
    CHECK(state_get() == STATE_HOLD && plan_get_current_block() != NULL);
    return EXIT_SUCCESS;
}
