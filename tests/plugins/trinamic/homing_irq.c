#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    tmc_mask(Setting_TrinamicHoming, X_AXIS_BIT);
    hal.limits.enable(true, (axes_signals_t){.x = On});
    trinamic_fault_handler();
    CHECK(!tmc_limit_irqs);
    hal.limits.enable(false, (axes_signals_t){0});
    trinamic_fault_handler();
    CHECK(tmc_limit_irqs == 1);
    return 0;
}
