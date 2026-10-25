#include "therm_host.h"
int main(void)
{
    therm_start(true);
    therm_report(false);
    CHECK(strstr(output, "|TH0:25.0|previous"));
    therm_report(false);
    CHECK(strcmp(output, "|previous") == 0);
    therm_report(true);
    CHECK(strstr(output, "|TH0:25.0|previous"));
    adc = 2000;
    therm_report(false);
    CHECK(strstr(output, "|TH0:") && reports == 4);
    return 0;
}
