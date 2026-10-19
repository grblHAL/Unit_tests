#include "support/registered_spindle_hold_observer_host.h"
int main(void)
{
    start_registered_spindle_hold();
    unsigned outputs = laser_output_calls, pulses = axis_pulses[X_AXIS];
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_STOP));
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_STOP));
    CHECK(protocol_exec_rt_system());
    state_suspend_manager();
    CHECK(held_programmed_calls == 0 && held_override_calls == 0);
    CHECK(laser_output_calls == outputs && laser_output_state.on);
    NEAR(laser_output_power, 500);
    CHECK(axis_pulses[X_AXIS] == pulses);
    CHECK(state_get() == STATE_HOLD && sys.suspend);
    return EXIT_SUCCESS;
}
