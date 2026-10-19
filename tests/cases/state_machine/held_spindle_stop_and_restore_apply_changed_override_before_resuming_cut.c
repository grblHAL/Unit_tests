#include "support/held_running_spindle_override_host.h"
int main(void)
{
    start_registered_running_hold();
    unsigned pulses = axis_pulses[X_AXIS];
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_COARSE_PLUS));
    CHECK(protocol_exec_rt_system());
    state_suspend_manager();
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_STOP));
    CHECK(protocol_exec_rt_system());
    state_suspend_manager();
    CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_STOP));
    CHECK(protocol_exec_rt_system());
    state_suspend_manager();
    CHECK(laser_output_state.on && laser_last_driver_level == 550);
    CHECK(axis_pulses[X_AXIS] == pulses && state_get() == STATE_HOLD);
    finish_registered_running_hold();
    CHECK(laser_last_driver_level == 550);
    return EXIT_SUCCESS;
}
