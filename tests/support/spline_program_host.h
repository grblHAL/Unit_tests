#pragma once
#include "support/canned_motion_host.h"
static int32_t spline_sample_x, spline_sample_y;
static bool spline_sample_seen;
static void sample_spline_pulse(stepper_t *stepper)
{
    pulse_driver(stepper);
    if(!spline_sample_seen && physical_position[X_AXIS] >= spline_sample_x) {
        spline_sample_seen = true;
        spline_sample_y = physical_position[Y_AXIS];
    }
}
static inline void prepare_spline_program(int32_t sample_x)
{
    prepare_canned_motion();
    spline_sample_x = sample_x;
    hal.stepper.pulse_start = sample_spline_pulse;
}
static inline void finish_spline_program(int32_t x, int32_t y, int32_t sample_y)
{
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == x && physical_position[X_AXIS] == x);
    CHECK(sys.position[Y_AXIS] == y && physical_position[Y_AXIS] == y);
    CHECK(axis_pulses[X_AXIS] == (unsigned)x && axis_pulses[Y_AXIS] == (unsigned)y);
    CHECK(axis_pulses[Z_AXIS] == 0);
    CHECK(spline_sample_seen);
    /* Closed-form Bezier sample plus allowance for flattening and pulse rounding. */
    CHECK(abs(spline_sample_y - sample_y) <= 24);
    NEAR(gc_state.position[X_AXIS], (float)x / settings.axis[X_AXIS].steps_per_mm);
    NEAR(gc_state.position[Y_AXIS], (float)y / settings.axis[Y_AXIS].steps_per_mm);
}
