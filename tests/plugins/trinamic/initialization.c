#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    CHECK(tmc_motors_get() == 3 && tmc_delays == 1 && !hal.stepper.status(false).fault.state);
    for (unsigned i = 0; i < 3; i++)
    {
        CHECK(tmc_drivers[i] && tmc_addresses[i] == i);
        const trinamic_config_t *cfg = tmc_drivers[i]->get_config(i);
        CHECK(cfg->current == 500 && cfg->microsteps == 16);
    }
    CHECK(tmc_reads > 0 && tmc_writes > 0);
    return 0;
}
