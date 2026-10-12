#pragma once
#include "support/engine_host.h"
#include "spindle_control.h"
#include "check.h"
static spindle_ptrs_t pwm_spindle;
static spindle_pwm_t pwm_data;
static spindle_pwm_settings_t pwm_settings;
static inline void prepare_spindle_pwm(void)
{
    engine_prepare();
    pwm_settings = (spindle_pwm_settings_t){.rpm_min = 1000, .rpm_max = 9000,
        .pwm_freq = 1000, .pwm_min_value = 10, .pwm_max_value = 90};
}
static inline void compute_spindle_pwm(void)
{
    CHECK(spindle_precompute_pwm_values(&pwm_spindle, &pwm_data, &pwm_settings, 1000000));
    CHECK(pwm_data.compute_value != NULL);
}
