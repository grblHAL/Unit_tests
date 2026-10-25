#include "therm_host.h"
int main(void)
{
    therm_start(true);
    therm_float(457, 5100);
    adc = 1551;
    CHECK(therm_command("THRMTEMP", STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(output, "25.0 degC"));
    adc = 3500;
    CHECK(therm_command("THRMTEMP", STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(output, "sensor error"));
    return 0;
}
