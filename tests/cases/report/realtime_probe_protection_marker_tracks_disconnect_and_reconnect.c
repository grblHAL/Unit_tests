#include "support/system_probe_guard_irq_host.h"

static void report_pending_probe_change(void)
{
    CHECK(hal.stream.report.flags.probe_protect);
    status_report_tracking_t tracking = {.flags = hal.stream.report.flags};
    report_realtime_status(hal.stream.write, &tracking);
}

int main(void)
{
    prepare_system_probe_guard();
    engine_output[0] = 0;
    report_pending_probe_change();
    CHECK(strstr(engine_output, "|P:0,P") != NULL);
    hal.probe.connected_toggle();
    CHECK(!hal.probe.get_state().connected && !hal.probe.get_state().irq_enabled);
    engine_output[0] = 0;
    report_pending_probe_change();
    CHECK(strstr(engine_output, "|P:0") != NULL);
    CHECK(strstr(engine_output, "|P:0,P") == NULL);
    hal.probe.connected_toggle();
    CHECK(hal.probe.get_state().connected && hal.probe.get_caps(Probe_Default).guarded);
    engine_output[0] = 0;
    report_pending_probe_change();
    CHECK(strstr(engine_output, "|P:0,P") != NULL);
    return EXIT_SUCCESS;
}
