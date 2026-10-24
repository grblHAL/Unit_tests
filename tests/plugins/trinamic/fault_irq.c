#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    trinamic_fault_handler();
    CHECK(tmc_limit_irqs == 1);
    return 0;
}
