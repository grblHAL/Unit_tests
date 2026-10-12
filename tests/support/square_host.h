#pragma once
#include "support/ganging_host.h"
#include "stepper.h"
static unsigned pulse_calls;
static unsigned motor_mask;
static void motor_pulse(stepper_t *stepper)
{
    pulse_calls++;
    motor_mask = stepper->step_out.bits;
}
static inline void prepare_square(void)
{
    prepare_ganging();
    hal.stepper.pulse_start = motor_pulse;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
}
