#pragma once
#include "support/multi_spindle_host.h"
/* RPM multiplication needs a relative-scale tolerance beyond the general NEAR macro. */
#define RPM_NEAR(actual, expected) CHECK(fabsf((actual) - (expected)) < .01f)
static unsigned rpm_update_calls, override_event_calls;
static float driver_rpm;
static void override_rpm_output(spindle_ptrs_t *spindle, float rpm)
{
    CHECK(spindle == spindle_get(0));
    driver_rpm = rpm;
    rpm_update_calls++;
}
static void override_event(override_changed_t changed)
{
    CHECK(changed == OverrideChanged_SpindleRPM);
    override_event_calls++;
}
static inline spindle_ptrs_t *prepare_spindle_override(void)
{
    prepare_multi_spindle_program();
    spindle_ptrs_t *spindle = spindle_get(0);
    spindle->update_rpm = override_rpm_output;
    CHECK(spindle_set_state(spindle, (spindle_state_t){.on = true}, 5000));
    grbl.on_override_changed = override_event;
    hal.stream.report.flags.value = 0;
    return spindle;
}
