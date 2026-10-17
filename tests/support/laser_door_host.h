#pragma once
#include "support/laser_stepper_host.h"
#include "support/parking_host.h"
static inline void run_laser_door_program(const char *program)
{
    prepare_laser_stepper();
    configure_parking_move();
    hal.signals_cap.safety_door_ajar = true;
    char actions[] = "3";
    CHECK(settings_store_setting(Setting_HoldActions, actions) == Status_OK);
    sys.cold_start = false;
    sys.driver_started = true;
    CHECK(laser_block(program) == Status_OK);
    state_set(STATE_CYCLE);
    for(unsigned ticks = 0; ticks < 100; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(physical_position[X_AXIS] > 0 && physical_position[X_AXIS] < 1600);
    bool initially_powered = laser_output_state.on && laser_output_power > 0;
    for(unsigned i = 0; i < laser_pwm_calls; i++) initially_powered |= laser_pwm_log[i] > 0;
    CHECK(initially_powered);
    park_until_retracted();
    CHECK(!laser_output_state.on);
    NEAR(laser_output_power, 0);
    CHECK(axis_pulses[Z_AXIS] == 0 && physical_position[Z_AXIS] == -800);
    unsigned held = axis_pulses[X_AXIS];
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_SAFETY_DOOR && axis_pulses[X_AXIS] == held);
    parking_door_open = false;
    system_set_exec_state_flag(EXEC_DOOR_CLOSED);
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_SAFETY_DOOR && axis_pulses[X_AXIS] == held);
    CHECK(!laser_output_state.on);
    laser_pwm_calls = 0;
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned ticks = 0; ticks < 200000 && state_get() != STATE_IDLE; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(protocol_exec_rt_system());
    }
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    CHECK(axis_pulses[Z_AXIS] == 0 && physical_position[Z_AXIS] == -800);
    bool powered = laser_output_state.on && laser_output_power > 0;
    for(unsigned i = 0; i < laser_pwm_calls; i++) powered |= laser_pwm_log[i] > 0;
    CHECK(powered && laser_output_state.on);
}
