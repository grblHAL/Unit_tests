#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    hal.stepper.enable((axes_signals_t){.mask = AXES_BITMASK}, true);
    tmc_state = STATE_CYCLE;
    tmc_block(X_AXIS);
    CHECK(tmc_drivers[0]->get_config(0)->current == 500 &&
          tmc_drivers[1]->get_config(1)->current == 250);
    tmc_block(Y_AXIS);
    CHECK(tmc_drivers[0]->get_config(0)->current == 250 &&
          tmc_drivers[1]->get_config(1)->current == 500 && tmc_pulse_calls == 2);
    return 0;
}
