#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    status_report_tracking_t tracking = {.flags={.m66result=true}};
    sys.var5399 = 42;
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|In:42") != NULL);
    engine_output[0] = '\0';
    tracking.flags.m66result = true;
    sys.var5399 = -1;
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|In:-1") != NULL);
    engine_output[0] = '\0';
    tracking.flags.m66result = true;
    sys.var5399 = -2;
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|In:") == NULL);
    return EXIT_SUCCESS;
}
