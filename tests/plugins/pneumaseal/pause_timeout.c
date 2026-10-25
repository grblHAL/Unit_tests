#include "seal_host.h"
int main(void)
{
    seal_start();
    seal_state(STATE_HOLD);
    CHECK(solenoid && timer_ms == 300000);
    seal_expire();
    CHECK(!solenoid);
    seal_state(STATE_SAFETY_DOOR);
    CHECK(solenoid && timer_ms == 300000);
    return 0;
}
