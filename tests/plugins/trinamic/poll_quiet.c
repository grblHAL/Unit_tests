#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    unsigned reads = tmc_reads;
    for (unsigned i = 0; i < 4; i++)
        tmc_poll();
    CHECK(tmc_reads > reads && !hal.stepper.status(false).warning.state && !tmc_holds &&
          !tmc_warn_reports);
    return 0;
}
