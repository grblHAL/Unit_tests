#pragma once
#include "support/spindle_pwm_host.h"
static inline void prepare_spindle_linearization(void)
{
    prepare_spindle_pwm();
    for(unsigned i = 0; i < SPINDLE_NPWM_PIECES; i++)
        pwm_settings.pwm_piece[i].rpm = NAN;
    pwm_settings.pwm_piece[0] = (pwm_piece_t){.rpm = 1000, .start = 1.0f, .end = 0};
    pwm_settings.pwm_piece[1] = (pwm_piece_t){.rpm = 5000, .start = 0.5f, .end = -2500};
}
