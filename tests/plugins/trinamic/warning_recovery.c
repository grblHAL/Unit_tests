#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    tmc_registers[0][TMC2209Reg_DRV_STATUS] = 1;
    for (unsigned i = 0; i < 3; i++)
        tmc_poll();
    CHECK(tmc_warn_reports == 1);
    tmc_registers[0][TMC2209Reg_DRV_STATUS] = 0;
    tmc_poll();
    CHECK(!hal.stepper.status(false).warning.state);
    tmc_registers[0][TMC2209Reg_DRV_STATUS] = 1;
    tmc_poll();
    tmc_poll();
    CHECK(tmc_warn_reports == 1);
    tmc_poll();
    CHECK(tmc_warn_reports == 2);
    return 0;
}
