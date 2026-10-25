#include "pulloff_host.h"
int main(void)
{
    load_pulloff();
    CHECK(saves == 1 && updates > 0 && details->settings->id == Setting_AxisExtended9);
    NEAR(get_pulloff(0), 12);
    NEAR(requested.values[0], 12);
    for (unsigned i = 1; i < N_AXIS; i++)
    {
        NEAR(get_pulloff(i), 2);
        NEAR(requested.values[i], 2);
    }
    grbl.on_report_options(true);
    CHECK(options == 1 && reports == 0);
    grbl.on_report_options(false);
    CHECK(options == 2 && reports == 1);
    return 0;
}
