#include "seal_host.h"
int main(void)
{
    seal_start();
    seal_setting(451, 7);
    seal_setting(452, 11);
    seal_setting(453, STATE_SLEEP);
    seal_setting(454, STATE_ALARM);
    seal_state(STATE_SLEEP);
    seal_state(STATE_IDLE);
    CHECK(timer_ms == 7000);
    seal_expire();
    CHECK(!solenoid);
    unsigned before = saves;
    registered_settings->restore();
    registered_settings->load();
    CHECK(saves == before + 1 && claims == 1 && seal_read_port() == 1 && seal_read(451) == 120 &&
          seal_read(452) == 300 &&
          seal_read(453) == (STATE_HOMING | STATE_CYCLE | STATE_JOG | STATE_TOOL_CHANGE) &&
          seal_read(454) == (STATE_HOLD | STATE_SAFETY_DOOR));
    seal_state(STATE_CYCLE);
    CHECK(solenoid && !timer);
    seal_state(STATE_HOLD);
    CHECK(solenoid && timer_ms == 300000);
    seal_state(STATE_IDLE);
    CHECK(solenoid && timer_ms == 120000);
    seal_expire();
    CHECK(!solenoid && warnings == 0);
    return 0;
}
