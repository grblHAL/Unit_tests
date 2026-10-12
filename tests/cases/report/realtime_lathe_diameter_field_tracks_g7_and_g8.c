#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    settings.mode = Mode_Lathe;
    char diameter[] = "G7";
    CHECK(gc_execute_block(diameter) == Status_OK);
    status_report_tracking_t tracking = {.flags={.xmode=true}};
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|D:1") != NULL);
    engine_output[0] = '\0';
    char radius[] = "G8";
    CHECK(gc_execute_block(radius) == Status_OK);
    tracking.flags.xmode = true;
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|D:0") != NULL);
    return EXIT_SUCCESS;
}
