#pragma once
#include "support/settings_host.h"
static axes_signals_t configured_ganged_axes = {.mask = 5};
static axes_signals_t configured_ganged(bool auto_squared)
{
    CHECK(!auto_squared);
    return configured_ganged_axes;
}
static inline void prepare_ganged_settings(void)
{
    prepare_settings_store();
    hal.stepper.get_ganged = configured_ganged;
}

