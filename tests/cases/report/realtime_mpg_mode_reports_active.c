#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report(); sys.mpg_mode = true;
    status_report_tracking_t tracking = {.flags = {.mpg_mode = true}};
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|MPG:1") != NULL);
    return EXIT_SUCCESS;
}
