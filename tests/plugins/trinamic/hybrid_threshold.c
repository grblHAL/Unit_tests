#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    CHECK(tmc_drivers[0]->get_config(0)->microsteps == 16);
    uint32_t initial_y = tmc_registers[1][TMC2209Reg_TPWMTHRS];
    tmc_axis_command(Trinamic_HybridThreshold, X_AXIS, 600);
    CHECK(tmc_registers[0][TMC2209Reg_TPWMTHRS] == 937);
    CHECK(tmc_registers[1][TMC2209Reg_TPWMTHRS] == initial_y);
    tmc_axis_command(Trinamic_HybridThreshold, Y_AXIS, 1200);
    CHECK(tmc_registers[1][TMC2209Reg_TPWMTHRS] == 468);
    CHECK(tmc_registers[0][TMC2209Reg_TPWMTHRS] == 937);
    tmc_axis_command(Trinamic_HybridThreshold, X_AXIS, 0);
    CHECK(tmc_registers[0][TMC2209Reg_TPWMTHRS] == 0);
    return 0;
}
