#include "support/build_report_host.h"
#include "check.h"
static probe_state_t build_probe_state(void) { return (probe_state_t){.connected = true}; }
static bool build_probe_select(probe_id_t id) { (void)id; return true; }
int main(void)
{
    prepare_build_report();
    hal.probe.get_state = build_probe_state;
    hal.probe.select = build_probe_select;
    hal.driver_cap.probe = hal.driver_cap.toolsetter = hal.driver_cap.probe2 = true;
    hal.signals_cap.probe_disconnected = true;
    build_report(true);
    CHECK(strstr(engine_output, ",PROBES=7,") != NULL);
    CHECK(strstr(engine_output, ",PC,") != NULL);
    CHECK(strstr(engine_output, "NOPROBE") == NULL);
    return EXIT_SUCCESS;
}
