#pragma once
#include "support/stepper_host.h"
#include "support/report_host.h"

static probe_state_t cycle_probe = {.connected = true};
static probe_state_t read_cycle_probe(void) { return cycle_probe; }
static inline void prepare_cycle_status_report(void)
{
    prepare_stepper();
    hal.stream.is_connected = connected;
    hal.coolant.get_state = coolant_state;
    hal.probe.get_state = read_cycle_probe;
    report_init_fns(); report_init();
    float target[N_AXIS] = {10};
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    data.condition.target_validated = data.condition.target_valid = true;
    CHECK(plan_buffer_line(target, &data));
    state_set(STATE_CYCLE);
    CHECK(state_get() == STATE_CYCLE && wake_calls == 1);
    settings.status_report.run_substate = true;
}
