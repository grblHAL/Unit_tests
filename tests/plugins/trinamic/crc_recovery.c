#include "tmc_host.h"
int main(void)
{
    tmc_crc_ok = false;
    tmc_prepare();
    tmc_start();
    CHECK(tmc_motors_get() == 0 && tmc_delays == 5 && tmc_warnings == 1);
    CHECK(hal.stepper.status(false).fault.state != 0);
    tmc_crc_ok = true;
    CHECK(!hal.stepper.status(true).fault.state && tmc_motors_get() == 3);
    tmc_axis_command(Trinamic_StepperCurrent, X_AXIS, 650);
    CHECK(tmc_drivers[0]->get_config(0)->current == 650);
    CHECK(tmc_drivers[1]->get_config(1)->current == 500);
    return 0;
}
