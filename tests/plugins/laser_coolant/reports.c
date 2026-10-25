#include "coolant_host.h"
int main(void)
{
    coolant_prepare(true);
    coolant_load();
    grbl.on_report_options(true);
    grbl.on_report_options(false);
    CHECK(coolant_prior_reports == 2 && coolant_plugins == 1);
    grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){.all = On});
    CHECK(strstr(coolant_text, "|previous"));
    return 0;
}
