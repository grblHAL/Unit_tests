#include "seal_host.h"
int main(void)
{
    seal_start();
    seal_state(STATE_CYCLE);
    seal_state(STATE_IDLE);
    CHECK(solenoid && timer_ms == 120000);
    seal_expire();
    CHECK(!solenoid && !timer);
    seal_state(STATE_IDLE);
    CHECK(!solenoid && !timer);
    return 0;
}
