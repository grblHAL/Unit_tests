#pragma once
#include "support/report_host.h"
#include "state_machine.h"
static coolant_state_t accessory_coolant;
static spindle_state_t accessory_spindle;
static coolant_state_t accessory_coolant_feedback(void) { return accessory_coolant; }
static spindle_state_t accessory_spindle_feedback(spindle_ptrs_t *spindle)
{ CHECK(spindle == spindle_get(0)); return accessory_spindle; }
static inline void prepare_accessory_report(void)
{
    prepare_report(); state_set(STATE_IDLE);
    hal.coolant.get_state = accessory_coolant_feedback;
    spindle_get(0)->get_state = accessory_spindle_feedback;
}
static inline void emit_accessory_report(void)
{
    status_report_tracking_t tracking = {.flags = {.coolant = true, .spindle = true}};
    report_realtime_status(hal.stream.write, &tracking);
}
