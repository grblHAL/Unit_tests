#include "support/boot_homing_inputs_host.h"

int main(void)
{
    boot_during_setup = install_home_switches;
    CHECK(grbl_enter() == 0);
    CHECK(hal.homing.get_state == dedicated_home_switches);
    home_signals_t state = hal.homing.get_state();
    CHECK(state.a.mask == 2 && state.b.mask == 4);
    return EXIT_SUCCESS;
}
