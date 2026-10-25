#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    CHECK(tmc_motors_get() == 3 && !hal.stepper.status(false).fault.state);
    for (unsigned motor = 0; motor < 3; motor++)
    {
        CHECK(tmc_drivers[motor]);
        const trinamic_config_t *config = tmc_drivers[motor]->get_config(motor);
        CHECK(config->current == 500 && config->microsteps == 16);
        CHECK(config->motor.id == motor && config->motor.axis == motor);
#if TRINAMIC_ENABLE == 2130
        CHECK(config->r_sense == 110);
#elif TRINAMIC_ENABLE == 5160
        CHECK(config->r_sense == 75);
#endif
    }
    CHECK(tmc_reads > 0 && tmc_writes > 0);
    return 0;
}
