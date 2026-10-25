#include "interlock_host.h"
int main(void)
{
    il_start();
    CHECK(il_float(900, 2) == Status_OK);
    levels[Port_Input][2] = 1;
    il_command(true);
    CHECK(hardware_spindles == 0 && resets == 1 && sys.rt_exec_alarm == Alarm_EStop);
    CHECK(strstr(warning, "FWD0 IN P2 high"));
    levels[Port_Input][2] = 0;
    il_command(true);
    CHECK(hardware_spindles == 1);
    return 0;
}
