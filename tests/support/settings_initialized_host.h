#pragma once
#include "support/settings_host.h"
static inline void prepare_initialized_settings(float minimum_pulse_us)
{
    prepare_settings_store();
    hal.step_us_min = minimum_pulse_us;
    settings.version.id = SETTINGS_VERSION;
    hal.nvs.put_byte(0, SETTINGS_VERSION);
    settings_write_global();
    settings_init();
    change_callbacks = 0;
}
