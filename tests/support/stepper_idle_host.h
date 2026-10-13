#pragma once
#include "support/stepper_host.h"
static unsigned motor_enable_calls;
static axes_signals_t last_motor_enable;
static bool last_motor_hold;
static void capture_motor_enable(axes_signals_t axes, bool hold)
{
    motor_enable_calls++;
    last_motor_enable = axes;
    last_motor_hold = hold;
}
static void prepare_stepper_idle(void)
{
    prepare_stepper();
    hal.stepper.enable = capture_motor_enable;
}
