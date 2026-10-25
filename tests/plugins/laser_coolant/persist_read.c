#include "coolant_host.h"
int main(void)
{
    coolant_inputs = 2;
    coolant_restore_image = true;
    coolant_prepare(true);
    coolant_load();
    NEAR(coolant_get_port(Setting_LaserCoolantOkPort), 1);
    NEAR(coolant_get_port(Setting_LaserCoolantTempPort), 1);
    hal.coolant.set_state((coolant_state_t){.flood = On});
    CHECK(coolant_output.flood && coolant_digital_port == 1 && coolant_irq_physical == 1);
    NEAR(coolant_wait_timeout, 2);
    NEAR(coolant_param("_laser_coolant_temp"), 25);
    CHECK(coolant_analog_port == 1);
    hal.coolant.set_state((coolant_state_t){0});
    CHECK(coolant_delay == 6000);
    coolant_run_delayed();
    CHECK(!coolant_output.flood);
    return 0;
}
