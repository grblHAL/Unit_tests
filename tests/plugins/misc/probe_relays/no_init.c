#include "relay_host.h"
int main(void)
{
    prepare_relays();
    probe_select_ptr original = hal.probe.select;
    on_report_options_ptr original_report = grbl.on_report_options;
#ifdef NO_PROBE
    hal.probe.get_state = NULL;
#elif defined(NATIVE_BOTH)
    hal.driver_cap.toolsetter = hal.driver_cap.probe2 = On;
#elif defined(NO_PORTS)
    available = 0;
#else
    alloc_ok = false;
#endif
    initialize_relays();
    CHECK(!relay_details && hal.probe.select == original &&
          grbl.on_report_options == original_report);
    CHECK(saves == 0 && writes == 0 && delays == 0);
#if defined(NO_PORTS) || defined(NO_ALLOCATION)
    CHECK(warnings == 1);
#else
    CHECK(warnings == 0);
#endif
    return 0;
}
