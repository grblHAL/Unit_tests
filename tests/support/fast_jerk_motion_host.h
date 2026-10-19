#pragma once
#include "support/fast_override_motion_host.h"
static void configure_fast_jerk_limits(void)
{
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        char jerk[] = "1000"; /* mm/s^3, through the public setting converter. */
        CHECK(settings_store_setting(Setting_AxisJerk + axis, jerk) == Status_OK);
    }
}
static inline void prepare_fast_jerk_motion(void)
{
    fast_configuration_hook = configure_fast_jerk_limits;
    prepare_fast_motion();
}
