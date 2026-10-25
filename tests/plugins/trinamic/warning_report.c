#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    tmc_registers[0][TMC2209Reg_DRV_STATUS] = (TMC2209_drv_status_reg_t){.otpw = 1}.value;
    tmc_poll();
    tmc_poll();
    CHECK(tmc_warn_reports == 0);
    tmc_poll();
    CHECK(tmc_warn_reports == 1 && strstr(tmc_output, "Over-Temperature Motor: X") && !tmc_holds);
    tmc_poll();
    CHECK(tmc_warn_reports == 1);
    return 0;
}
