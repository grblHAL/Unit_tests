#include "support/engine_host.h"
#include "report.h"
#include <string.h>
#include "check.h"
static bool connected(void) { return true; }
int main(void)
{
    engine_prepare();
    hal.stream.is_connected = connected;
    report_init_fns();
    report_init();
    report_add_realtime(Report_MPGMode);
    CHECK(!(hal.stream.report.flags.value & Report_MPGMode));
    hal.driver_cap.mpg_mode = true;
    report_add_realtime(Report_MPGMode);
    CHECK(hal.stream.report.flags.value & Report_MPGMode);
    return EXIT_SUCCESS;
}
