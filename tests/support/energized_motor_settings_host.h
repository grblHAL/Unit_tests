#pragma once
#include "support/settings_host.h"
static unsigned motor_enable_calls;
static axes_signals_t requested_motor_mask;
static void configure_enabled_motors(axes_signals_t mask, bool hold)
{
    CHECK(hold);
    requested_motor_mask = mask; motor_enable_calls++;
}
static inline void prepare_energized_motor_settings(void)
{
    prepare_settings_store(); hal.stepper.enable = configure_enabled_motors;
}
