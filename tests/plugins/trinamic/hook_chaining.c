#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    grbl.on_report_options(true);
    grbl.on_report_options(false);
    grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){0});
    hal.limits.enable(false, (axes_signals_t){0});
    CHECK(tmc_previous_settings == 1 && tmc_previous_reports == 2 && tmc_previous_realtime == 1 &&
          tmc_previous_limits == 1);
    CHECK(strstr(tmc_output, ",TMC=7") && strstr(tmc_output, "|Previous:1"));
    return 0;
}
