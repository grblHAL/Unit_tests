#pragma once
#include "support/settings_host.h"
static unsigned probe_connection_toggles;
static void toggle_probe_connection(void) { probe_connection_toggles++; }
static control_signals_t connection_controls(void) { return (control_signals_t){0}; }
static inline void prepare_probe_connection_setting(void)
{
    prepare_settings_store();
    hal.signals_cap.probe_disconnected = hal.signals_cap.reset = true;
    hal.control.get_state = connection_controls;
    hal.probe.connected_toggle = toggle_probe_connection;
}
static inline status_code_t store_disconnection_inversion(void)
{
    char value[16];
    snprintf(value, sizeof(value), "%u", (unsigned)(control_signals_t){.probe_disconnected = true}.mask);
    return store_setting(Setting_ControlInvertMask, value);
}
