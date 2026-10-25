#include "therm_host.h"
int main(void)
{
    therm_start(true);
    CHECK(therm_command("THRMTEMP", STATE_IDLE, "999") == Status_OK);
    CHECK(stops == 1 && sys.rt_exec_alarm == Alarm_Spindle && reads == 0);
    CHECK(strstr(output, "simulating over-temp"));
    return 0;
}
