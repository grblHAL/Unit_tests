#include "support/laser_hold_host.h"
int main(void)
{
    start_laser_hold_move_actions("G1X20F100M4S500", "0");
    hold_motion();
    state_suspend_manager();
    CHECK(laser_output_state.on);
    CHECK(laser_pwm_calls > 0 && laser_pwm_log[laser_pwm_calls - 1] == 0);
    unsigned held = axis_pulses[X_AXIS];
    laser_pwm_calls = 0;
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(axis_pulses[X_AXIS] == held);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE);
    CHECK(axis_pulses[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    bool powered = false;
    for(unsigned i = 0; i < laser_pwm_calls; i++) powered |= laser_pwm_log[i] > 0;
    CHECK(powered && laser_pwm_log[laser_pwm_calls - 1] == 0);
    return EXIT_SUCCESS;
}
