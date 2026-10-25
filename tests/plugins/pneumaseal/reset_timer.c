#include "seal_host.h"
int main(void)
{
    seal_start();
    hal.driver_reset();
    CHECK(!timer && !solenoid);
    seal_state(STATE_CYCLE);
    hal.driver_reset();
    CHECK(solenoid && timer_ms == 120000);
    seal_expire();
    CHECK(!solenoid);
    return 0;
}
