#pragma once
#include "support/boot_host.h"

static bool driver_probe_connected;
static unsigned driver_probe_toggles;
static probe_state_t driver_probe_state(void)
{
    return (probe_state_t){ .probe_id = Probe_Default, .connected = driver_probe_connected };
}
static void toggle_driver_probe(void)
{
    driver_probe_connected = !driver_probe_connected;
    driver_probe_toggles++;
}
static void install_probe_connection(settings_t *current)
{
    CHECK(current == &settings);
    hal.driver_cap.probe = true;
    hal.signals_cap.probe_disconnected = true;
    hal.probe.get_state = driver_probe_state;
    hal.probe.connected_toggle = toggle_driver_probe;
}
