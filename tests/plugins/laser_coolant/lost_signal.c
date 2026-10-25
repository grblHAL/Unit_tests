#include "coolant_host.h"
int main(void)
{
    coolant_prepare(true);
    coolant_load();
    hal.coolant.set_state((coolant_state_t){.flood = On});
    coolant_edge(false);
    CHECK(sys.rt_exec_alarm == Alarm_AbortCycle);
    hal.coolant.set_state((coolant_state_t){0});
    sys.rt_exec_alarm = 0;
    coolant_edge(false);
    CHECK(!sys.rt_exec_alarm);
    return 0;
}
