#include "therm_host.h"
int main(void)
{
    therm_start(true);
    adc = 1000;
    for (unsigned i = 0; i < 8; i++)
        therm_report(false);
    CHECK(stops == 0 && sys.rt_exec_alarm == 0);
    return 0;
}
