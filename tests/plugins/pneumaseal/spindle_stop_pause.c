#include "seal_host.h"
int main(void)
{
    seal_start();
    seal_state(STATE_HOLD);
    seal_spindle(true);
    CHECK(solenoid && !timer);
    seal_spindle(false);
    CHECK(timer_ms == 300000);
    seal_state(STATE_CYCLE);
    seal_spindle(true);
    seal_spindle(false);
    CHECK(solenoid && !timer);
    return 0;
}
