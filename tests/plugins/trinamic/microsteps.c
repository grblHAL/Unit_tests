#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    CHECK(tmc_set(Setting_AxisMicroSteps, X_AXIS, 32) == Status_OK);
    CHECK(tmc_drivers[0]->get_config(0)->microsteps == 32);
    CHECK(tmc_set(Setting_AxisMicroSteps, X_AXIS, 3) == Status_InvalidStatement);
    CHECK(tmc_drivers[0]->get_config(0)->microsteps == 32 &&
          tmc_drivers[1]->get_config(1)->microsteps == 16);
    return 0;
}
