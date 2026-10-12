#include <string.h>
#include "hal.h"
#include "check.h"

int main(void)
{
    hal.limits_cap.max.mask = 2; hal.limits_cap.max2.mask = 2;
    xbar_set_homing_source(); axes_signals_t cycle = {.mask = 3};
    limit_signals_t src = xbar_get_homing_source_from_cycle(cycle);
    CHECK(src.max.mask == 2); CHECK(src.min.mask == 1);
    CHECK((src.max.mask | src.min.mask) == cycle.mask);
    return EXIT_SUCCESS;
}
