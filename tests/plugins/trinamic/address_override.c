#include "tmc_host.h"
int main(void)
{
    tmc_custom_address = true;
    tmc_prepare();
    tmc_start();
    for (unsigned i = 0; i < 3; i++)
        CHECK(tmc_addresses[i] == i + 1 && tmc_drivers[i]->get_config(i)->motor.address == i + 1);
    return 0;
}
