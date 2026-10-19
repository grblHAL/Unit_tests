#pragma once
#include "support/laser_stepper_host.h"
#include "support/hold_host.h"
static coolant_state_t running_hold_coolant(void) { return (coolant_state_t){0}; }
static inline void prepare_registered_running_spindle(void)
{
    prepare_pwm_stepper_mode(Mode_Standard);
    sys.cold_start = false;
    sys.driver_started = true;
    hal.coolant.get_state = running_hold_coolant;
    settings.flags.restore_after_feed_hold = true;
    CHECK(laser_block("M3S500") == Status_OK);
}
static inline void start_registered_running_hold(void)
{
    prepare_registered_running_spindle();
    CHECK(laser_block("G1X20F100") == Status_OK);
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned tick = 0; tick < 100; tick++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    hold_motion();
    CHECK(!spindle_get(0)->cap.laser);
    CHECK(laser_last_driver_level == 500);
}
static inline void change_held_running_spindle(uint8_t command, unsigned percent, unsigned pwm)
{
    CHECK(state_get() == STATE_HOLD && sys.holding_state == Hold_Complete);
    unsigned pulses = axis_pulses[X_AXIS];
    CHECK(protocol_enqueue_realtime_command(command));
    CHECK(protocol_exec_rt_system());
    state_suspend_manager();
    CHECK(state_get() == STATE_HOLD && sys.suspend);
    CHECK(laser_output_state.on && !laser_output_state.ccw);
    CHECK(spindle_get(0)->param->override_pct == percent);
    CHECK(axis_pulses[X_AXIS] == pulses);
    fprintf(stderr, "registered held PWM: actual=%u expected=%u overridden=%g pending=%u\n", (unsigned)laser_last_driver_level, pwm, (double)spindle_get(0)->param->rpm_overridden, (unsigned)sys.step_control.update_spindle_rpm);
    CHECK(laser_last_driver_level == pwm);
    CHECK(!sys.step_control.update_spindle_rpm);
}
static inline void finish_registered_running_hold(void)
{
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    CHECK(sys.position[X_AXIS] == 1600);
}
