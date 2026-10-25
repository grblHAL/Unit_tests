#include "seal_host.h"
int main(void)
{
    seal_start();
    seal_setting(453, STATE_SLEEP);
    seal_setting(454, STATE_ALARM);
    seal_setting(451, 7);
    seal_setting(452, 11);
    seal_state(STATE_SLEEP);
    CHECK(solenoid && !timer);
    seal_state(STATE_ALARM);
    CHECK(solenoid && timer_ms == 11000);
    seal_state(STATE_IDLE);
    CHECK(timer_ms == 7000);
    return 0;
}
