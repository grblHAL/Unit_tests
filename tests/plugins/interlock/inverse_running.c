#include "interlock_host.h"
int main(void)
{
    il_start();
    CHECK(il_float(912, 2) == Status_OK);
    spindle_state_t s = {0};
    s.on = 1;
    grbl.on_spindle_programmed(&spindle, s, 1000, SpindleSpeedMode_RPM);
    hal.port.digital_out(2, true);
    CHECK(hardware_outputs == 0 && resets == 1 && sys.rt_exec_alarm == Alarm_EStop &&
          warnings == 0);
    grbl.on_execute_realtime(STATE_CYCLE);
    CHECK(warnings == 1 && strstr(warning, "P2 blocked"));
    grbl.on_execute_realtime(STATE_CYCLE);
    CHECK(warnings == 1);
    return 0;
}
