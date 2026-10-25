#include "tmc_host.h"
int main(void)
{
    tmc_bus_ok = false;
    tmc_prepare();
    tmc_start();
    CHECK(tmc_motors_get() == 0 && tmc_delays == 5 && tmc_warnings == 1);
    CHECK(hal.stepper.status(false).fault.state != 0);
    return 0;
}
