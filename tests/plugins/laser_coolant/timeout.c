#include "coolant_host.h"
int main(void)
{
    coolant_prepare(true);
    coolant_settings->restore();
    coolant_float(Setting_LaserCoolantOnDelay, 2);
    coolant_settings->save();
    coolant_load();
    coolant_signal = false;
    hal.coolant.set_state((coolant_state_t){.flood = On, .mist = On});
    CHECK(!coolant_output.flood && coolant_output.mist && coolant_reads == 1);
    CHECK(sys.rt_exec_alarm == Alarm_AbortCycle);
    return 0;
}
