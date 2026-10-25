#include "coolant_host.h"
int main(void)
{
    coolant_change_cap = false;
    coolant_prepare(true);
    CHECK(coolant_port(Setting_LaserCoolantOkPort, 0) == Status_AuxiliaryPortUnusable);
    coolant_load();
    CHECK(!coolant_has_param("_laser_coolant_ok"));
    hal.coolant.set_state((coolant_state_t){.flood = On});
    CHECK(coolant_output.flood && !coolant_irqs);
    return 0;
}
