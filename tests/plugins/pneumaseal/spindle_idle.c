#include "seal_host.h"
int main(void)
{
    seal_start();
    seal_spindle(true);
    CHECK(solenoid && !timer);
    seal_state(STATE_IDLE);
    CHECK(solenoid && !timer);
    seal_spindle(false);
    CHECK(solenoid && timer_ms == 120000);
    seal_expire();
    CHECK(!solenoid);
    return 0;
}
