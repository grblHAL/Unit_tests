#include "coolant_host.h"
int main(void)
{
    coolant_inputs = 2;
    coolant_prepare(true);
    CHECK(coolant_port(Setting_LaserCoolantOkPort, 1) == Status_OK);
    CHECK(coolant_port(Setting_LaserCoolantTempPort, 1) == Status_OK);
    coolant_settings->save();
    coolant_load();
    NEAR(coolant_param("_laser_coolant_ok"), 1);
    NEAR(coolant_param("_laser_coolant_temp"), 25);
    CHECK(coolant_digital_port == 1 && coolant_analog_port == 1);
    hal.coolant.set_state((coolant_state_t){.flood = On});
    CHECK(coolant_irqs == 1 && coolant_irq_physical == 1);
    coolant_edge(false);
    CHECK(sys.rt_exec_alarm == Alarm_AbortCycle);
    return 0;
}
