#include "support/multiple_probe_report_host.h"

int main(void)
{
    prepare_multiple_probe_report();
    for(unsigned i = 0; i < 3; i++) probe_inputs[i] = true;
    status_report_tracking_t tracking = {.flags = report_get_rt_flags_all()};
    report_realtime_status(hal.stream.write, &tracking);
    fprintf(stderr, "%s", engine_output);
    CHECK(strstr(engine_output, "|Pn:PIJK") != NULL);
    CHECK(strstr(engine_output, "|P:2") != NULL);
    CHECK(strstr(engine_output, "|P:2,P") == NULL);
    CHECK(tracking.probe_states.aquired);
    CHECK(tracking.probe_states.probe_triggered);
    CHECK(tracking.probe_states.toolsetter_triggered);
    CHECK(tracking.probe_states.probe2_triggered);
    return EXIT_SUCCESS;
}
