#include "support/laser_hold_host.h"
int main(void)
{
    start_laser_hold_move_actions("G1X20F100M3S500", "6");
    unsigned writes = laser_output_calls;
    hold_motion();
    CHECK(laser_output_state.on && !laser_output_state.ccw);
    CHECK(laser_output_calls == writes + 1);
    NEAR(laser_output_power, 0);
    CHECK(spindle_get(0)->param->option.restore_rpm);
    NEAR(gc_spindle_get(0)->rpm, 500);
    unsigned held = axis_pulses[X_AXIS];
    for(unsigned i = 0; i < 4; i++) {
        state_suspend_manager();
        CHECK(axis_pulses[X_AXIS] == held && laser_last_driver_level == 0);
    }
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(axis_pulses[X_AXIS] == held);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    CHECK(laser_output_state.on && laser_last_driver_level == 500);
    CHECK(!spindle_get(0)->param->option.restore_rpm);
    CHECK(sys.alarm == Alarm_None && !sys.abort);
    return EXIT_SUCCESS;
}
