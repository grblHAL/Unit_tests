#include "seal_host.h"
int main(void)
{
    seal_start();
    seal_setting(451, 0);
    seal_setting(452, 0);
    seal_state(STATE_CYCLE);
    seal_state(STATE_IDLE);
    CHECK(!solenoid && !timer);
    seal_state(STATE_HOLD);
    CHECK(!solenoid && !timer);
    return 0;
}
