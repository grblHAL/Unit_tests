#include "support/boot_homing_inputs_host.h"

int main(void)
{
    CHECK(grbl_enter() == 0);
    boot_limit_signals.min.mask = 5;
    boot_limit_signals.min2.mask = 2;
    home_signals_t state = hal.homing.get_state();
    CHECK(state.a.mask == 5 && state.b.mask == 2);
    return EXIT_SUCCESS;
}
