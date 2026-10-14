#pragma once
#include "support/spindle_slot_settings_host.h"
static coolant_state_t secondary_status_coolant(void) { return (coolant_state_t){0}; }
static inline void prepare_secondary_status_report(void)
{
    prepare_settings_mapped_spindles();
    hal.control.get_state = spindle_controls;
    hal.stream.is_connected = spindle_connected;
    hal.coolant.get_state = secondary_status_coolant;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
}
static inline void expect_secondary_status(const char *field)
{
    engine_output[0] = 0;
    status_report_tracking_t tracking = {0};
    report_realtime_status(hal.stream.write, &tracking);
    const char *found = strstr(engine_output, field);
    CHECK(found != NULL);
    CHECK(found[strlen(field)] == '|' || found[strlen(field)] == '>');
}
