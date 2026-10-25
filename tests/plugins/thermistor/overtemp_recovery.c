#include "therm_host.h"
int main(void)
{
    therm_start(true);
    therm_float(459, 20);
    for (unsigned i = 0; i < 4; i++)
        therm_report(false);
    adc = 3600;
    therm_report(false);
    adc = 3102;
    for (unsigned i = 0; i < 4; i++)
    {
        therm_report(false);
        CHECK(stops == 0);
    }
    therm_report(false);
    CHECK(stops == 1);
    return 0;
}
