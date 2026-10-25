#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    CHECK(tmc_motors_get() == 3 && tmc_reads > 0 && tmc_writes > 0);
    CHECK(tmc_unexpected_spi == 0);
    return 0;
}
