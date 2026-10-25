#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    tmc_registers[0][TMC2209Reg_DRV_STATUS] = (TMC2209_drv_status_reg_t){.otpw = 1}.value;
    tmc_state = STATE_CYCLE;
    tmc_block(X_AXIS);
    for (unsigned i = 0; i < 3; i++)
        tmc_poll();
    CHECK(tmc_holds == 1 && tmc_warn_reports == 1);
    return 0;
}
