#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    CHECK(tmc_set(Setting_AxisMicroSteps, X_AXIS, 32) == Status_OK);
    CHECK(tmc_drivers[0]->get_config(0)->microsteps == 32);
#if TRINAMIC_ENABLE == 2130
    TMC2130_chopconf_reg_t actual = {.value = tmc_registers[0][TMC2130Reg_CHOPCONF]};
#elif TRINAMIC_ENABLE == 2240
    TMC2240_chopconf_reg_t actual = {.value = tmc_registers[0][TMC2240Reg_CHOPCONF]};
#elif TRINAMIC_ENABLE == 2660
    TMC2660_drvctrl_reg_t actual = {.dgr.value = tmc_registers[0][TMC2660Reg_DRVCTRL]};
#elif TRINAMIC_ENABLE == 5160
    TMC5160_chopconf_reg_t actual = {.value = tmc_registers[0][TMC5160Reg_CHOPCONF]};
#endif
#if TRINAMIC_ENABLE != 2209
    CHECK(actual.mres == 3);
#endif
    CHECK(tmc_set(Setting_AxisMicroSteps, X_AXIS, 3) == Status_InvalidStatement);
    CHECK(tmc_drivers[0]->get_config(0)->microsteps == 32 &&
          tmc_drivers[1]->get_config(1)->microsteps == 16);
    return 0;
}
