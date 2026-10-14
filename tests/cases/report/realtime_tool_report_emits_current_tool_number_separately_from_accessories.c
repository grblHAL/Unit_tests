#include "support/accessory_report_host.h"

int main(void)
{
    prepare_accessory_report();
    gc_state.tool->tool_id = 7;
    status_report_tracking_t tracking = {.flags = {.tool = true}};
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|A:|T:7>") != NULL);
    return EXIT_SUCCESS;
}
