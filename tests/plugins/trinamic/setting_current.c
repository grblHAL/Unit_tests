#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    CHECK(tmc_set(Setting_AxisStepperCurrent, Y_AXIS, 750) == Status_OK);
    CHECK(tmc_drivers[1]->get_config(1)->current == 750 &&
          tmc_drivers[0]->get_config(0)->current == 500);
    return 0;
}
