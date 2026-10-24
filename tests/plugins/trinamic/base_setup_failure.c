#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_load();
    tmc_setup_ok = false;
    CHECK(!hal.driver_setup(&settings));
    CHECK(!tmc_reads && !tmc_writes && tmc_warnings == 1);
    return 0;
}
