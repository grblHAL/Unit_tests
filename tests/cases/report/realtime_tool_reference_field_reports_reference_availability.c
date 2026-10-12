#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    status_report_tracking_t tracking = {.flags={.tlo_reference=true}};
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|TLR:0") != NULL);
    engine_output[0] = '\0';
    sys.tlo_reference_set.mask = Z_AXIS_BIT;
    tracking.flags.tlo_reference = true;
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|TLR:1") != NULL);
    return EXIT_SUCCESS;
}
