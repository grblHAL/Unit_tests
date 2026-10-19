#pragma once
#include "support/canned_motion_host.h"
static int32_t partial_peck_deepest_z;
static void partial_peck_pulse(stepper_t *stepper)
{
    pulse_driver(stepper);
    if(physical_position[Z_AXIS] < partial_peck_deepest_z)
        partial_peck_deepest_z = physical_position[Z_AXIS];
}
static inline void prepare_partial_peck_motion(void)
{
    prepare_canned_motion();
    hal.stepper.pulse_start = partial_peck_pulse;
}
