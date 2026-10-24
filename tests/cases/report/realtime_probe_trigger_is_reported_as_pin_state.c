#include "support/realtime_pins_host.h"
#include "check.h"

int main(void)
{
    prepare_realtime_pins(); realtime_probe.triggered = true;
    realtime_report(); CHECK(strstr(engine_output, "|Pn:P>") != NULL);
    status_report_tracking_t tracking = {.flags = {.all = true}};
    engine_output[0] = 0;
    report_realtime_status(hal.stream.write, &tracking);
    const char *pins = strstr(engine_output, "|Pn:");
    CHECK(pins != NULL && pins[4] == 'P' && strcspn(pins + 4, "|>") == 1);
    CHECK(!tracking.probe_states.aquired);
    realtime_probe.triggered = false;
    realtime_controls.feed_hold = true;
    tracking.flags.all = true;
    engine_output[0] = 0;
    report_realtime_status(hal.stream.write, &tracking);
    pins = strstr(engine_output, "|Pn:");
    CHECK(pins != NULL && pins[4] == 'H' && strcspn(pins + 4, "|>") == 1);
    CHECK(!tracking.probe_states.aquired);
    tracking.flags.all = false;
    tracking.flags.extended = true;
    engine_output[0] = 0;
    report_realtime_status(hal.stream.write, &tracking);
    pins = strstr(engine_output, "|Pn:");
    CHECK(pins != NULL && pins[4] == 'H' && strcspn(pins + 4, "|>") == 1);
    CHECK(!tracking.probe_states.aquired);
    return EXIT_SUCCESS;
}
