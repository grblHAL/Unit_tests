#include "seal_host.h"
int main(void)
{
    seal_start();
    CHECK(seal_read_port() == 1 && seal_read(451) == 120 && seal_read(452) == 300 &&
          seal_read(453) == (STATE_HOMING | STATE_CYCLE | STATE_JOG | STATE_TOOL_CHANGE) &&
          seal_read(454) == (STATE_HOLD | STATE_SAFETY_DOOR));
    seal_setting(451, 7);
    seal_setting(452, 11);
    seal_setting(453, STATE_SLEEP);
    seal_setting(454, STATE_ALARM);
    registered_settings->save();
    seal_setting(451, 99);
    seal_setting(452, 101);
    seal_setting(453, STATE_CYCLE);
    seal_setting(454, STATE_HOLD);
    registered_settings->load();
    CHECK(seal_read(451) == 7 && seal_read(452) == 11 && seal_read(453) == STATE_SLEEP &&
          seal_read(454) == STATE_ALARM && saves == 2 && claims == 1);
    seal_state(STATE_SLEEP);
    CHECK(solenoid && !timer);
    seal_state(STATE_ALARM);
    CHECK(solenoid && timer_ms == 11000);
    seal_state(STATE_IDLE);
    CHECK(solenoid && timer_ms == 7000);
    return 0;
}
