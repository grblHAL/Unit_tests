#pragma once
#include "support/css_host.h"
#include "motion_control.h"
static unsigned lathe_cycle_calls;
static uint32_t lathe_cycle_label;
static lathe_cycle_arguments_t lathe_cycle_args;
static plan_line_data_t lathe_cycle_plan;
// Capture the weak plugin replacement interface; no cycle geometry is simulated.
status_code_t mc_lathe_cycle(plan_line_data_t *data, coord_data_t *position,
    uint32_t label, lathe_cycle_arguments_t *args)
{
    CHECK(position == (coord_data_t *)gc_state.position);
    lathe_cycle_calls++; lathe_cycle_label = label;
    lathe_cycle_args = *args; lathe_cycle_plan = *data; return Status_OK;
}
static inline void prepare_lathe_capture(void)
{ prepare_css_parser(true); CHECK(css_block("G18") == Status_OK); }
