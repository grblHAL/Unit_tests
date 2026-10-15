#pragma once
#include "support/report_host.h"
static void prepare_mixed_axis_report(void)
{
    prepare_report();
    CHECK(N_AXIS == 8);
    settings.steppers.is_rotary.mask = (1u << 3) | (1u << 4) | (1u << 5);
    settings.flags.report_inches = true;
    report_init();
    for(unsigned i = 0; i < N_AXIS; i++) settings.axis[i].steps_per_mm = 100;
}
