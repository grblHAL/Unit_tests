#include "coolant_host.h"
int main(void)
{
    coolant_prepare(true);
    coolant_settings->restore();
    coolant_float(Setting_LaserCoolantOffDelay, 0.1f);
    coolant_settings->save();
    coolant_load();
    hal.coolant.set_state((coolant_state_t){.flood = On});
    hal.coolant.set_state((coolant_state_t){0});
    CHECK(coolant_delay == 6000);
    hal.coolant.set_state((coolant_state_t){.flood = On});
    CHECK(coolant_output.flood && !coolant_delay && !sys.rt_exec_alarm);
    return 0;
}
