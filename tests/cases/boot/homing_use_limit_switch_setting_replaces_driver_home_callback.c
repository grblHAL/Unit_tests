#include "support/boot_homing_inputs_host.h"

int main(void)
{
    boot_during_setup = install_home_switches;
    use_limits = true;
    CHECK(grbl_enter() == 0);
    CHECK(hal.homing.get_state != dedicated_home_switches);
    boot_limit_signals.min.mask = 1;
    boot_limit_signals.min2.mask = 2;
    home_signals_t state = hal.homing.get_state();
    CHECK(state.a.mask == 1 && state.b.mask == 2);
    return EXIT_SUCCESS;
}
