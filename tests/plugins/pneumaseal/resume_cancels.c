#include "seal_host.h"
int main(void)
{
    seal_start();
    seal_state(STATE_HOLD);
    CHECK(timer);
    seal_state(STATE_CYCLE);
    CHECK(solenoid && !timer);
    seal_state(STATE_IDLE);
    CHECK(timer_ms == 120000);
    seal_state(STATE_JOG);
    CHECK(solenoid && !timer);
    return 0;
}
