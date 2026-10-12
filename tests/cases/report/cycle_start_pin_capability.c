#include "support/engine_host.h"
#include "report.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    report_add_realtime(Report_CycleStart);
    CHECK(!(hal.stream.report.flags.value & Report_CycleStart));
    settings.status_report.pin_state = true;
    report_add_realtime(Report_CycleStart);
    CHECK(hal.stream.report.flags.value & Report_CycleStart);
    return EXIT_SUCCESS;
}
