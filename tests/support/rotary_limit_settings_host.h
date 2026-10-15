#pragma once
#include "support/settings_initialized_host.h"
static bool rotary_limit_driver_enabled;
static unsigned rotary_limit_driver_calls;
static void configure_rotary_limits(bool enabled, axes_signals_t cycle)
{
    CHECK(cycle.mask == 0);
    rotary_limit_driver_enabled = enabled; rotary_limit_driver_calls++;
}
static inline void prepare_rotary_limit_settings(void)
{
    prepare_initialized_settings(2);
    hal.limits.enable = configure_rotary_limits;
    CHECK(store_setting(Settings_RotaryAxes, "5") == Status_OK);
    CHECK(settings.steppers.is_rotary.mask == 40);
    change_callbacks = 0;
}
