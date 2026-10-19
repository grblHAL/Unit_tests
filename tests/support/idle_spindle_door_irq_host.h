#pragma once
#include "support/laser_stepper_host.h"
static bool idle_door_open;
static control_signals_t idle_door_controls(void) { return (control_signals_t){.safety_door_ajar = idle_door_open}; }
static coolant_state_t idle_door_coolant(void) { return (coolant_state_t){0}; }
static void idle_door_set_coolant(coolant_state_t state) { CHECK(state.mask == 0); }
static inline void prepare_idle_door_spindle(machine_mode_t mode, bool ignore_idle)
{
    prepare_pwm_stepper_mode(mode);
    sys.cold_start = false;
    sys.driver_started = true;
    hal.signals_cap.safety_door_ajar = true;
    hal.control.get_state = idle_door_controls;
    hal.control.interrupt_callback = control_interrupt_handler;
    hal.coolant.get_state = idle_door_coolant;
    hal.coolant.set_state = idle_door_set_coolant;
    char flags[] = {ignore_idle ? '1' : '0', '\0'};
    CHECK(settings_store_setting(Setting_DoorOptions, flags) == Status_OK);
    // Constant laser output requires a cutting modal state, even without axis words.
    CHECK(laser_block(mode == Mode_Laser ? "G1M3S500F100" : "M3S500") == Status_OK);
    CHECK(state_get() == STATE_IDLE && laser_output_state.on && laser_last_driver_level == 500);
}
static inline void open_idle_spindle_door(void)
{
    idle_door_open = true;
    hal.control.interrupt_callback((control_signals_t){.safety_door_ajar = true});
}
static inline void check_idle_door_no_motion(void)
{
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(axis_pulses[axis] == 0 && physical_position[axis] == 0 && sys.position[axis] == 0);
    }
    CHECK(plan_get_current_block() == NULL);
}
