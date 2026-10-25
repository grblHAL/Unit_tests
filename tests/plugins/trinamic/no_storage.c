#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_storage_ok = false;
    CHECK(!trinamic_init() && !tmc_settings && tmc_reads == 0 && tmc_writes == 0);
    return 0;
}
