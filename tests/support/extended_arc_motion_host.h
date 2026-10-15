#pragma once
#include "support/motion_program_host.h"
static bool auxiliary_motion_during_arc;
static unsigned observed_curve_axis = X_AXIS;
static void observe_extended_arc_pulse(stepper_t *stepper)
{
    pulse_driver(stepper);
    if(axis_pulses[observed_curve_axis] > 0 &&
       physical_position[observed_curve_axis] != 80 && axis_pulses[3] > 0)
        auxiliary_motion_during_arc = true;
}
static inline void prepare_extended_arc_motion(void)
{
    prepare_motion_program();
    hal.stepper.pulse_start = observe_extended_arc_pulse;
}
static inline void check_extended_arc_endpoint(const int32_t expected[N_AXIS])
{
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == expected[axis]);
        CHECK(physical_position[axis] == expected[axis]);
        if(axis >= 3) CHECK(axis_pulses[axis] == (unsigned)abs(expected[axis]));
    }
    CHECK(auxiliary_motion_during_arc);
}
