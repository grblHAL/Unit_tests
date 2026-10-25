#include "support/multiple_probe_report_host.h"
static void check_probe_pin_field(status_report_tracking_t *tracking, bool all, const char *expected)
{
    tracking->flags.all = all;
    tracking->flags.extended = !all;
    engine_output[0] = '\0';
    report_realtime_status(hal.stream.write, tracking);
    const char *field = strstr(engine_output, "|Pn:");
    CHECK(field != NULL);
    field += 4;
    CHECK(strcspn(field, "|>") == strlen(expected));
    CHECK(strncmp(field, expected, strlen(expected)) == 0);
}
int main(void)
{
    prepare_multiple_probe_report();
    /* A held control input keeps the pin field present while individual probes release. */
    realtime_controls.feed_hold = true;
    status_report_tracking_t tracking = {0};
    check_probe_pin_field(&tracking, true, "H");
    CHECK(tracking.probe_states.aquired);
    probe_inputs[1] = true;
    check_probe_pin_field(&tracking, false, "HJ");
    check_probe_pin_field(&tracking, false, "H");
    probe_inputs[1] = false;
    check_probe_pin_field(&tracking, false, "Hj");
    probe_inputs[0] = true;
    check_probe_pin_field(&tracking, false, "HI");
    probe_inputs[0] = false;
    check_probe_pin_field(&tracking, false, "Hi");
    CHECK(!tracking.probe_states.probe_triggered && !tracking.probe_states.toolsetter_triggered);
    CHECK(!tracking.probe_states.probe2_triggered);
    return EXIT_SUCCESS;
}
