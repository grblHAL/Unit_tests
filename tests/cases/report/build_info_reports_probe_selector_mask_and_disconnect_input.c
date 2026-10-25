#include "support/build_report_host.h"
#include "check.h"
static probe_state_t build_probe_state(void) { return (probe_state_t){.connected = true}; }
static bool build_probe_select(probe_id_t id) { (void)id; return true; }
int main(void)
{
    prepare_build_report();
    hal.probe.get_state = build_probe_state;
    for(unsigned pass = 0; pass < 3; pass++) {
        bool selectable = pass != 1;
        hal.probe.select = selectable ? build_probe_select : NULL;
        hal.driver_cap.probe = true;
        hal.driver_cap.toolsetter = hal.driver_cap.probe2 = selectable;
        hal.signals_cap.probe_disconnected = selectable;
        engine_output[0] = 0;
        build_options_calls = 0;
        build_report(true);
        CHECK((strstr(engine_output, ",PROBES=7,") != NULL) == selectable);
        CHECK((strstr(engine_output, ",PC,") != NULL) == selectable);
        if(!selectable) CHECK(strstr(engine_output, "PROBES=") == NULL);
        CHECK(strstr(engine_output, "NOPROBE") == NULL);
    }
    return EXIT_SUCCESS;
}
