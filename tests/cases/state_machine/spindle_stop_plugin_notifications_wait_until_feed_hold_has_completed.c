#include "support/registered_spindle_hold_observer_host.h"
int main(void)
{
    start_registered_spindle_motion();
    CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_HOLD && sys.holding_state == Hold_Pending);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_STOP));
    CHECK(protocol_exec_rt_system());
    state_suspend_manager();
    CHECK(held_programmed_calls == 0 && held_override_calls == 0);
    CHECK(laser_output_state.on);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(sys.holding_state == Hold_Complete);
    unsigned pulses = axis_pulses[X_AXIS];
    state_suspend_manager();
    CHECK(held_programmed_calls == 1 && held_override_calls == 1);
    CHECK(held_previous_hardware[0].on && !held_programmed_state[0].on);
    CHECK(!laser_output_state.on && !held_override_hardware[0].on);
    CHECK(axis_pulses[X_AXIS] == pulses);
    return EXIT_SUCCESS;
}
