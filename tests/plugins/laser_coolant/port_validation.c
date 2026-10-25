#include "coolant_host.h"
int main(void)
{
    coolant_inputs = 2;
    coolant_prepare(true);
    CHECK(coolant_port(Setting_LaserCoolantOkPort, 0.5f) == Status_BadNumberFormat);
    CHECK(coolant_port(Setting_LaserCoolantTempPort, 0.5f) == Status_BadNumberFormat);
    CHECK(coolant_port(Setting_LaserCoolantOkPort, 2) == Status_AuxiliaryPortUnavailable);
    CHECK(coolant_port(Setting_LaserCoolantTempPort, 2) == Status_AuxiliaryPortUnavailable);
    CHECK(coolant_port(Setting_LaserCoolantOkPort, 1) == Status_OK);
    CHECK(coolant_port(Setting_LaserCoolantTempPort, 1) == Status_OK);
    NEAR(coolant_get_port(Setting_LaserCoolantOkPort), 1);
    NEAR(coolant_get_port(Setting_LaserCoolantTempPort), 1);
    return 0;
}
