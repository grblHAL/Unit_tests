#include "coolant_host.h"
int main(void)
{
    coolant_prepare(true);
    coolant_settings->restore();
    coolant_float(Setting_LaserCoolantOffDelay, 1);
    coolant_settings->save();
    coolant_load();
    hal.coolant.set_state((coolant_state_t){.flood = On});
    sys.reset_pending = true;
    hal.coolant.set_state((coolant_state_t){0});
    CHECK(!coolant_output.flood && !coolant_delay);
    return 0;
}
