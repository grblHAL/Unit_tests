#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    hal.stepper.enable((axes_signals_t){.mask = AXES_BITMASK}, true);
    for (unsigned i = 0; i < 3; i++)
        CHECK(tmc_drivers[i]->get_config(i)->current == 250);
    CHECK(tmc_enable_calls == 1);
    return 0;
}
