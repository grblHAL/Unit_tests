#pragma once
#include "support/spindle_caps_host.h"
#include "state_machine.h"
#include "protocol.h"
static spindle_state_t ramp_hardware_state;
static uint_fast16_t ramp_pwm_log[64];
static unsigned ramp_pwm_calls, ramp_state_calls;
static float ramp_initial_rpm;
static spindle_state_t ramp_state_log[16];
static void ramp_set_state(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle == spindle_get(0)); CHECK(ramp_state_calls < 16);
    ramp_state_log[ramp_state_calls++] = state; ramp_hardware_state = state;
    ramp_initial_rpm = rpm;
}
static spindle_state_t ramp_get_state(spindle_ptrs_t *spindle)
{ CHECK(spindle == spindle_get(0)); return ramp_hardware_state; }
static void ramp_update_pwm(spindle_ptrs_t *spindle, uint_fast16_t pwm)
{
    CHECK(spindle == spindle_get(0)); CHECK(ramp_pwm_calls < 64);
    ramp_pwm_log[ramp_pwm_calls++] = pwm;
}
static inline spindle_ptrs_t *prepare_spindle_ramp(void)
{
    spindle_ptrs_t *configured = prepare_spindle_caps(false);
    settings.spindle.on_delay = settings.spindle.off_delay = 500;
    pwm_data.flags.ramp_pwm = true; spindle_update_caps(configured,&pwm_data);
    spindle_ptrs_t *active = spindle_get(0);
    active->set_state = ramp_set_state; active->get_state = ramp_get_state;
    active->update_pwm = ramp_update_pwm;
    state_set(STATE_IDLE); sys.cold_start = false; sys.driver_started = true;
    return active;
}
static inline void clear_ramp_records(void)
{ ramp_pwm_calls = ramp_state_calls = 0; engine_ticks = 0; }
