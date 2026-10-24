#include "tmc_host.h"
int main(void)
{
    tmc_bus_ok = false;
    tmc_prepare();
    tmc_start();
    CHECK(tmc_motors_get() == 0);
    tmc_bus_ok = true;
    CHECK(!hal.stepper.status(true).fault.state && tmc_motors_get() == 3);
    return 0;
}
