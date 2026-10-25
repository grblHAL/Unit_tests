#include "coolant_host.h"
int main(void)
{
    coolant_prepare(true);
    coolant_settings->restore();
    coolant_float(Setting_LaserCoolantOffDelay, 0.1f);
    coolant_settings->save();
    coolant_load();
    hal.coolant.set_state((coolant_state_t){.flood = On, .mist = On});
    hal.coolant.set_state((coolant_state_t){.mist = On});
    CHECK(coolant_output.flood && coolant_delay == 6000);
    coolant_edge(false);
    CHECK(!sys.rt_exec_alarm);
    coolant_run_delayed();
    CHECK(!coolant_output.flood && coolant_output.mist && coolant_reports == 1);
    return 0;
}
