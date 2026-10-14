#include "hal.h"
#include "check.h"
int main(void)
{
    hal.home_cap.a.mask = AXES_BITMASK;
    hal.limits_cap.max.mask = AXES_BITMASK;
    hal.limits_cap.max2.mask = AXES_BITMASK;
    xbar_set_homing_source();
    limit_signals_t fallback = xbar_get_homing_source_from_cycle((axes_signals_t){.mask = X_AXIS_BIT});
    CHECK(fallback.min.mask == 0 && fallback.max.mask == 0);
    CHECK(fallback.min2.mask == 0 && fallback.max2.mask == 0);
    return EXIT_SUCCESS;
}
