#pragma once
#include "support/settings_host.h"
#include "support/spindle_pwm_host.h"
static inline void prepare_linearization_settings(void)
{
    prepare_settings_store();
    settings.pwm_spindle.rpm_min = 1000;
    settings.pwm_spindle.rpm_max = 9000;
    settings.pwm_spindle.pwm_freq = 1000;
    settings.pwm_spindle.pwm_min_value = 10;
    settings.pwm_spindle.pwm_max_value = 90;
    for(unsigned i = 0; i < SPINDLE_NPWM_PIECES; i++)
        settings.pwm_spindle.pwm_piece[i].rpm = NAN;
}
