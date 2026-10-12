#include <string.h>
#include "hal.h"
#include "check.h"

int main(void)
{
    hal.limits_cap.max.mask = 3; hal.limits_cap.max2.mask = 4;
    settings.homing.dir_mask.mask = 1;
    xbar_set_homing_source(); limit_signals_t src = xbar_get_homing_source();
    CHECK(src.max.mask == 2); CHECK(src.min.mask == 5);
    CHECK(src.max2.mask == 4); CHECK(src.min2.mask == 3);
    return EXIT_SUCCESS;
}
