#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    tmc_mask(Setting_TrinamicHoming, X_AXIS_BIT);
    tmc_sensitivity(Setting_AxisExtended0, X_AXIS, 30);
    tmc_sensitivity(Setting_AxisExtended2, X_AXIS, 10);
    hal.limits.enable(true, (axes_signals_t){.x = On});
    CHECK(grbl.on_homing_rate_set);
    coord_data_t rates = {.values = {120, 120, 120}};
    grbl.on_homing_rate_set((axes_signals_t){.x = On}, &rates, HomingMode_Seek);
    CHECK(tmc_registers[0][TMC2209Reg_SGTHRS] == 30);
    grbl.on_homing_rate_set((axes_signals_t){.x = On}, &rates, HomingMode_Locate);
    CHECK(tmc_registers[0][TMC2209Reg_SGTHRS] == 10);
    hal.limits.enable(false, (axes_signals_t){0});
    grbl.on_homing_rate_set((axes_signals_t){.x = On}, &rates, HomingMode_Seek);
    CHECK(tmc_registers[0][TMC2209Reg_SGTHRS] == 10 && tmc_previous_limits == 2);
    return 0;
}
