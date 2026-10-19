#include "support/laser_hold_host.h"
int main(void)
{
    start_laser_hold_move_actions("G1X20F100M3S500", "0");
    unsigned outputs = laser_output_calls;
    hold_motion();
    state_suspend_manager();
    CHECK(laser_output_state.on);
    NEAR(laser_output_power, 500);
    CHECK(laser_output_calls == outputs);
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE);
    CHECK(axis_pulses[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    CHECK(laser_output_state.on);
    NEAR(laser_output_power, 500);
    return EXIT_SUCCESS;
}
