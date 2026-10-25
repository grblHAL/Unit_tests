#include "therm_host.h"
int main(void)
{
    therm_start(true);
    grbl.on_report_options(true);
    CHECK(options == 1);
    grbl.on_report_options(false);
    CHECK(options == 3);
    return 0;
}
