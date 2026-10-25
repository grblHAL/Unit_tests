#include "therm_host.h"
int main(void)
{
    therm_start(true);
    CHECK(therm_command("THRMTEMP", STATE_IDLE, "1") == Status_OK);
    CHECK(strstr(output, "raw=3102") && strstr(output, "v_mcu=") && strstr(output, "r_ntc="));
    adc = 0;
    CHECK(therm_command("THRMTEMP", STATE_IDLE, "1") == Status_OK);
    CHECK(strstr(output, "sensor error") && strstr(output, "r_ntc=OOB"));
    return 0;
}
