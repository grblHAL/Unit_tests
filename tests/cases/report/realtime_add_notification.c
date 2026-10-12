#include "support/engine_host.h"
#include "report.h"
#include "check.h"
static unsigned calls;
static report_tracking_flags_t seen;
static void added(report_tracking_flags_t flags) { calls++; seen = flags; }
int main(void)
{
    engine_prepare();
    grbl.on_rt_reports_added = added;
    report_add_realtime(Report_WCO);
    CHECK(calls == 1);
    CHECK(seen.value == Report_WCO);
    CHECK(hal.stream.report.flags.value & Report_WCO);
    return EXIT_SUCCESS;
}
