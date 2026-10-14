#pragma once
#include "support/spindle_pwm_host.h"
static unsigned caps_output_calls;
static void caps_set_state(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{ (void)spindle; (void)rpm; CHECK(!state.on); caps_output_calls++; }
static spindle_state_t caps_get_state(spindle_ptrs_t *spindle)
{ (void)spindle; return (spindle_state_t){0}; }
static void caps_update_pwm(spindle_ptrs_t *spindle, uint_fast16_t pwm)
{ (void)spindle; (void)pwm; CHECK(false); }
static uint_fast16_t caps_get_pwm(spindle_ptrs_t *spindle, float rpm)
{ return spindle->context.pwm->compute_value(spindle->context.pwm, rpm, false); }
static inline spindle_ptrs_t *prepare_spindle_caps(bool laser)
{
    prepare_spindle_pwm(); sys.cold_start = true;
    settings.mode = laser ? Mode_Laser : Mode_Standard;
    pwm_spindle = (spindle_ptrs_t){.type=SpindleType_PWM,.ref_id=1,
        .set_state=caps_set_state,.get_state=caps_get_state,.update_pwm=caps_update_pwm,.get_pwm=caps_get_pwm};
    compute_spindle_pwm(); spindle_update_caps(&pwm_spindle,&pwm_data);
    CHECK(spindle_register(&pwm_spindle,"PWM host") == 0); CHECK(spindle_select(0));
    CHECK(spindle_get(0) != NULL);
    return spindle_get_hal(0,SpindleHAL_Configured);
}
