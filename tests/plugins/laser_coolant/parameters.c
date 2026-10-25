#include "coolant_host.h"
int main(void)
{
    coolant_prepare(true);
    coolant_load();
    NEAR(coolant_param("_laser_coolant_ok"), 1);
    NEAR(coolant_param("_laser_coolant_temp"), 25);
    coolant_signal = false;
    coolant_temperature = 315;
    NEAR(coolant_param("_laser_coolant_ok"), 0);
    NEAR(coolant_param("_laser_coolant_temp"), 31.5f);
    return 0;
}
