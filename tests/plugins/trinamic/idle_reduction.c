#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    tmc_state = STATE_CYCLE;
    tmc_block(X_AXIS);
    CHECK(tmc_drivers[0]->get_config(0)->current == 500);
    tmc_state = STATE_IDLE;
    tmc_poll();
    CHECK(tmc_drivers[0]->get_config(0)->current == 250);
    return 0;
}
