#include "tmc_host.h"
int main(void)
{
    tmc_bus_ok = false;
    tmc_prepare();
    tmc_start();
    CHECK(tmc_motors_get() == 0);
#if TRINAMIC_ENABLE == 2660
    CHECK(tmc_delays == 5 && tmc_retry_delays == 25 * 3 * 5);
#endif
    tmc_bus_ok = true;
    CHECK(!hal.stepper.status(true).fault.state && tmc_motors_get() == 3);
    return 0;
}
