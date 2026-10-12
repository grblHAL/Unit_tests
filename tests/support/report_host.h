#pragma once
#include "support/engine_host.h"
#include "report.h"
#include "check.h"
#include <string.h>
static bool connected(void) { return true; }
static coolant_state_t coolant_state(void) { return (coolant_state_t){0}; }
static inline void prepare_report(void)
{
    engine_parser_prepare();
    hal.stream.is_connected = connected;
    hal.coolant.get_state = coolant_state;
    report_init_fns();
    report_init();
}
static inline void realtime_report(void)
{
    status_report_tracking_t tracking = {0};
    report_realtime_status(hal.stream.write, &tracking);
}
