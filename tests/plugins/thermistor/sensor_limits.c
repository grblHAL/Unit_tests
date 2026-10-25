#include "therm_host.h"
int main(void)
{
    therm_start(true);
    int32_t values[] = {-1, 0, 4095, 4096};
    for (unsigned i = 0; i < 4; i++)
    {
        adc = values[i];
        CHECK(therm_command("THRMTEMP", STATE_IDLE, NULL) == Status_OK);
        CHECK(strstr(output, "sensor error"));
        therm_report(true);
        CHECK(strcmp(output, "|previous") == 0);
    }
    CHECK(stops == 0);
    return 0;
}
