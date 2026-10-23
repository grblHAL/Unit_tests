#include "support/laser_hold_host.h"
int main(void)
{
    start_laser_hold_move_actions("G1X20F100M4S500", "6");
    CHECK(settings.flags.set_rpm_0_during_hold && settings.flags.restore_after_feed_hold);
    unsigned writes = laser_output_calls;
    hold_motion();
    CHECK(laser_output_calls == writes);
    CHECK(laser_output_state.on && laser_output_state.ccw);
    CHECK(laser_last_driver_level == 0);
    CHECK(!spindle_get(0)->param->option.restore_rpm);
    unsigned held = axis_pulses[X_AXIS];
    for(unsigned i = 0; i < 4; i++) {
        state_suspend_manager();
        CHECK(laser_last_driver_level == 0 && laser_output_calls == writes);
        CHECK(axis_pulses[X_AXIS] == held);
    }
    laser_pwm_calls = 0;
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(axis_pulses[X_AXIS] == held && laser_last_driver_level == 0);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    bool powered = false;
    for(unsigned i = 0; i < laser_pwm_calls; i++) powered |= laser_pwm_log[i] > 0;
    CHECK(powered && laser_last_driver_level == 0);
    CHECK(sys.alarm == Alarm_None && !sys.abort);
    return EXIT_SUCCESS;
}
