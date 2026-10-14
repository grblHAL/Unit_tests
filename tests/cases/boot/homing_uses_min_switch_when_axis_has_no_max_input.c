#include "support/boot_homing_inputs_host.h"

int main(void)
{
    boot_limit_signals.max.mask = 1;
    CHECK(grbl_enter() == 0);
    settings.homing.dir_mask.mask = 0;
    xbar_set_homing_source();
    boot_limit_signals.min.mask = 6;
    boot_limit_signals.max.mask = 1;
    home_signals_t state = hal.homing.get_state();
    CHECK(state.a.mask == 7);
    return EXIT_SUCCESS;
}
