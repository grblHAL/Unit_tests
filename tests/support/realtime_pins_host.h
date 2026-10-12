#pragma once
#include "support/report_host.h"
static control_signals_t realtime_controls;
static limit_signals_t realtime_limits;
static probe_state_t realtime_probe = {.connected = true};
static control_signals_t read_realtime_controls(void) { return realtime_controls; }
static limit_signals_t read_realtime_limits(void) { return realtime_limits; }
static probe_state_t read_realtime_probe(void) { return realtime_probe; }
static inline void prepare_realtime_pins(void)
{
    prepare_report(); settings.status_report.pin_state = true;
    hal.control.get_state = read_realtime_controls;
    hal.limits.get_state = read_realtime_limits;
    hal.probe.get_state = read_realtime_probe;
}
