#pragma once
#include "support/laser_stepper_host.h"
#include "support/hold_host.h"
static unsigned held_programmed_calls, held_override_calls;
static spindle_state_t held_programmed_state[8], held_previous_hardware[8], held_override_hardware[8];
static float held_programmed_rpm[8];
static int32_t held_programmed_position[8];
static coolant_state_t held_no_coolant(void) { return (coolant_state_t){0}; }
static void held_programmed(spindle_ptrs_t *spindle, spindle_state_t state, float rpm, spindle_rpm_mode_t mode)
{
    CHECK(spindle == spindle_get(0) && mode == SpindleSpeedMode_RPM);
    CHECK(held_programmed_calls < 8);
    unsigned i = held_programmed_calls++;
    held_programmed_state[i] = state;
    held_programmed_rpm[i] = rpm;
    held_previous_hardware[i] = laser_output_state;
    held_programmed_position[i] = physical_position[X_AXIS];
}
static void held_override(override_changed_t changed)
{
    CHECK(changed == OverrideChanged_SpindleState && held_override_calls < 8);
    held_override_hardware[held_override_calls++] = laser_output_state;
}
static inline void start_registered_spindle_motion(void)
{
    prepare_pwm_stepper_mode(Mode_Standard);
    sys.cold_start = false;
    sys.driver_started = true;
    hal.coolant.get_state = held_no_coolant;
    settings.flags.restore_after_feed_hold = true;
    CHECK(laser_block("M3S500G1X20F100") == Status_OK);
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned ticks = 0; ticks < 100; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(laser_output_state.on);
    NEAR(laser_output_power, 500);
    grbl.on_spindle_programmed = held_programmed;
    grbl.on_override_changed = held_override;
}
static inline void start_registered_spindle_hold(void)
{
    start_registered_spindle_motion();
    hold_motion();
}
static inline void toggle_registered_held_spindle(void)
{
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_STOP));
    CHECK(protocol_exec_rt_system());
    state_suspend_manager();
    CHECK(state_get() == STATE_HOLD && sys.holding_state == Hold_Complete);
    CHECK(gc_spindle_get(0)->state.on);
    NEAR(gc_spindle_get(0)->rpm, 500);
}

