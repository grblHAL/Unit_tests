#pragma once
#include "support/settings_host.h"
static unsigned probe_configure_calls, probe_select_calls;
static probe_state_t settings_probe_state(void) { return (probe_state_t){0}; }
static void settings_probe_configure(bool away, bool probing)
{
    CHECK(!away && !probing);
    probe_configure_calls++;
}
static bool settings_probe_select(probe_id_t id) { (void)id; probe_select_calls++; return true; }
static inline void prepare_probe_settings(void)
{
    prepare_settings_store();
    hal.probe.get_state = settings_probe_state;
    hal.probe.configure = settings_probe_configure;
    hal.probe.select = settings_probe_select;
}
