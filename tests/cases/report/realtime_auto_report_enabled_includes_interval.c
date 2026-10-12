#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report(); settings.report_interval = 250; sys.flags.auto_reporting = true;
    status_report_tracking_t tracking = {.flags = {.mpg_mode = true}};
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|AR:250|MPG:0") != NULL);
    return EXIT_SUCCESS;
}
