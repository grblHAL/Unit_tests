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
    report_add_realtime(Report_WCO);
    report_add_realtime(Report_TLOReference);
    CHECK(hal.stream.report.flags.value & Report_WCO);
    CHECK(hal.stream.report.flags.value & Report_TLOReference);
    report_add_realtime(Report_ClearAll);
    CHECK(hal.stream.report.flags.value == 0);
    return EXIT_SUCCESS;
}
