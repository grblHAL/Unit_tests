#pragma once
#include "support/hold_host.h"
#include "support/report_host.h"
static inline void prepare_refresh_cycle(void)
{
    start_hold_move();
    hal.stream.is_connected = connected; hal.coolant.get_state = coolant_state;
    settings.status_report.overrides = settings.status_report.work_coord_offset = true;
    report_init();
    report_add_realtime(Report_ClearAll);
}
static inline void next_refresh_report(void)
{
    engine_output[0] = '\0';
    report_realtime_status(hal.stream.write, &hal.stream.report);
}
