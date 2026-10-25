#include "coolant_host.h"
int main(void)
{
    coolant_prepare(true);
    CHECK(coolant_port(Setting_LaserCoolantTempPort, -1) == Status_OK);
    NEAR(coolant_get_port(Setting_LaserCoolantTempPort), -1);
    coolant_settings->save();
    coolant_load();
    CHECK(coolant_has_param("_laser_coolant_ok") && !coolant_has_param("_laser_coolant_temp"));
    hal.coolant.set_state((coolant_state_t){.flood = On});
    CHECK(coolant_output.flood && coolant_irqs == 1);
    return 0;
}
