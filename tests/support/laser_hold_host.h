#pragma once
#include "support/laser_stepper_host.h"
#include "support/hold_host.h"
static coolant_state_t laser_hold_coolant(void) { return (coolant_state_t){0}; }
static inline void start_laser_hold_move_actions(const char *program, const char *hold_actions)
{
    prepare_laser_stepper();
    hal.coolant.get_state = laser_hold_coolant;
    sys.cold_start = false;
    sys.driver_started = true;
    char actions[4];
    CHECK(strlen(hold_actions) < sizeof(actions));
    strcpy(actions, hold_actions);
    CHECK(settings_store_setting(Setting_HoldActions, actions) == Status_OK);
    CHECK(laser_block(program) == Status_OK);
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_CYCLE);
    for(unsigned ticks = 0; ticks < 100; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(physical_position[X_AXIS] > 0 && physical_position[X_AXIS] < 1600);
}
static inline void start_laser_hold_move(const char *program)
{
    start_laser_hold_move_actions(program, "1");
}
static inline void hold_laser_and_resume(void)
{
    hold_motion();
    state_suspend_manager();
    CHECK(!laser_output_state.on);
    NEAR(laser_output_power, 0);
    unsigned held_pulses = axis_pulses[X_AXIS];
    for(unsigned i = 0; i < 3; i++) {
        state_suspend_manager();
        CHECK(axis_pulses[X_AXIS] == held_pulses);
        CHECK(!laser_output_state.on);
        NEAR(laser_output_power, 0);
    }
    laser_pwm_calls = 0;
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_CYCLE);
    CHECK(axis_pulses[X_AXIS] == held_pulses);
    NEAR(laser_output_power, 0);
    for(unsigned i = 0; i < laser_pwm_calls; i++)
        CHECK(laser_pwm_log[i] == 0);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE);
    CHECK(sys.position[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    CHECK(axis_pulses[X_AXIS] == 1600);
    CHECK(plan_get_current_block() == NULL);
    bool powered_after_resume = false;
    for(unsigned i = 0; i < laser_pwm_calls; i++)
        powered_after_resume |= laser_pwm_log[i] > 0;
    CHECK(powered_after_resume);
}
