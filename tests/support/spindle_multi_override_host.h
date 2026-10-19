#pragma once
#include "support/multi_spindle_modal_host.h"
static inline void prepare_independent_spindle_overrides(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();
    spindle_set_override(spindle_get(0), 110);
    spindle_set_override(spindle_get(1), 120);
    CHECK(fabsf(actual_spindle_rpm[0] - 3300.0f) < 0.01f); CHECK(fabsf(actual_spindle_rpm[1] - 8400.0f) < 0.01f);
}
static inline void check_independent_spindle_override_outputs(float primary, float secondary)
{
    // Percentage scaling uses float arithmetic; allow less than one hundredth RPM.
    CHECK(fabsf(actual_spindle_rpm[0] - primary) < 0.01f); CHECK(fabsf(actual_spindle_rpm[1] - secondary) < 0.01f);
    CHECK(spindle_get(0)->param->override_pct == 110 && spindle_get(1)->param->override_pct == 120);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    CHECK(spindle_output_calls[2] == 0);
}
