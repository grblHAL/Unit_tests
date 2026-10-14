#include "support/boot_homing_inputs_host.h"

int main(void)
{
    boot_limit_signals.max.mask = 7;
    boot_limit_signals.max2.mask = 7;
    CHECK(grbl_enter() == 0);
    settings.homing.dir_mask.mask = 5;
    xbar_set_homing_source();
    boot_limit_signals.min.mask = 1;
    boot_limit_signals.max.mask = 6;
    boot_limit_signals.min2.mask = 4;
    boot_limit_signals.max2.mask = 3;
    home_signals_t state = hal.homing.get_state();
    CHECK(state.a.mask == 3 && state.b.mask == 6);
    return EXIT_SUCCESS;
}
