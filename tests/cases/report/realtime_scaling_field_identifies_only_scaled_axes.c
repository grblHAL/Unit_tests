#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    char scale[] = "G51X2Y3Z1";
    CHECK(gc_execute_block(scale) == Status_OK);
    status_report_tracking_t tracking = {.flags={.scaling=true}};
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|Sc:XY") != NULL);
    return EXIT_SUCCESS;
}
