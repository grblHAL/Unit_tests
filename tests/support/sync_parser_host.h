#pragma once
#include "support/css_host.h"
#include "protocol.h"
#include "report.h"
static spindle_data_t sync_feedback;
static void sync_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle == spindle_get(0));
    (void)state;
    (void)rpm;
}
static spindle_data_t *sync_data(spindle_data_request_t request)
{
    (void)request;
    return &sync_feedback;
}
static inline void prepare_sync_parser(void)
{
    prepare_css_parser(true);
    spindle_get(0)->set_state = sync_output;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns();
    report_init();
    spindle_get(0)->get_data = sync_data;
    sync_feedback.rpm = 2000.0f;
    CHECK(css_block("G18M3S2000") == Status_OK);
}
