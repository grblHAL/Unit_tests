#include "support/laser_hold_host.h"

int main(void)
{
    start_laser_hold_move_actions("G1X20F100M5S500", "0");
    CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    hold_motion();
    state_suspend_manager();
    unsigned stopped = axis_pulses[X_AXIS];
    CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    for(unsigned poll = 0; poll < 4; poll++) {
        state_suspend_manager();
        CHECK(axis_pulses[X_AXIS] == stopped);
        CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    }
    laser_pwm_calls = 0;
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_CYCLE && axis_pulses[X_AXIS] == stopped);
    CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    for(unsigned ticks = 0; ticks < 200000 && !(sys.rt_exec_state & EXEC_CYCLE_COMPLETE); ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    }
    CHECK(sys.rt_exec_state & EXEC_CYCLE_COMPLETE);
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    for(unsigned i = 0; i < laser_pwm_calls; i++) CHECK(laser_pwm_log[i] == 0);

    laser_pwm_calls = 0;
    CHECK(laser_block("G1X21M3S500") == Status_OK);
    bool powered = laser_last_driver_level > 0;
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    powered |= laser_last_driver_level > 0;
    for(unsigned i = 0; i < laser_pwm_calls; i++) powered |= laser_pwm_log[i] > 0;
    CHECK(powered);
    CHECK(axis_pulses[X_AXIS] == 1680 && physical_position[X_AXIS] == 1680);
    CHECK(sys.position[X_AXIS] == 1680 && state_get() == STATE_IDLE);
    CHECK(plan_get_current_block() == NULL && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
