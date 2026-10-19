#pragma once
#include "support/wco_motion_host.h"
static unsigned wco_status_samples;
static const char *expected_work_positions[2], *expected_work_offsets[2];
static status_report_tracking_t motion_status_tracking;
static bool motion_report_connected(void) { return true; }
static control_signals_t motion_report_controls(void) { return (control_signals_t){0}; }
static coolant_state_t motion_report_coolant(void) { return (coolant_state_t){0}; }
static void sample_wco_status(void)
{
    if(wco_status_samples >= 2) return;
    int32_t sample = wco_status_samples ? 120 : 40;
    if(physical_position[X_AXIS] != sample) return;
    engine_output[0] = '\0';
    report_realtime_status(hal.stream.write, &motion_status_tracking);
    CHECK(strstr(engine_output, expected_work_positions[wco_status_samples]));
    CHECK(strstr(engine_output, expected_work_offsets[wco_status_samples]));
    wco_status_samples++;
}
static inline void prepare_wco_status_motion(void)
{
    prepare_motion_program();
    hal.stream.is_connected = motion_report_connected;
    hal.control.get_state = motion_report_controls;
    hal.coolant.get_state = motion_report_coolant;
    settings.status_report.sync_on_wco_change = false;
    settings.status_report.work_coord_offset = true;
    report_init();
    observe_wco_motion_tick = sample_wco_status;
}
