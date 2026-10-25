#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    tmc_axis_command(Trinamic_StepperCurrent, X_AXIS, 700);
    CHECK(tmc_drivers[0]->get_config(0)->current == 700 &&
          tmc_drivers[1]->get_config(1)->current == 500);
    return 0;
}
