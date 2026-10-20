#pragma once
#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "check.h"
void asymmetric_ganging_init(void);
static unsigned settings_callbacks;
static unsigned ganging_options_calls;
static bool ganging_new_options;
static axes_signals_t (*ganging_driver_axes)(bool auto_squared);
static void ganging_options(bool newopt)
{ ganging_options_calls++; ganging_new_options = newopt; }
static limit_signals_t fixture_limits;
static void settings_changed(settings_t *current, settings_changed_flags_t changed)
{
    CHECK(current == &settings);
    (void)changed;
    settings_callbacks++;
}
static limit_signals_t limits_state(void) { return fixture_limits; }
static bool connected(void) { return true; }
static inline void prepare_ganging(void)
{
    engine_prepare();
    hal.stream.is_connected = connected;
    hal.limits.get_state = limits_state;
    grbl.on_settings_changed = settings_changed;
    grbl.on_report_options = ganging_options;
    hal.stepper.get_ganged = ganging_driver_axes;
    asymmetric_ganging_init();
}
