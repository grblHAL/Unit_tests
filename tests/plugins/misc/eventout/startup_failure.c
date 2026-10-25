#include "event_host.h"
int main(void)
{
#ifdef EVENT_NO_PORTS
    available_ports = 0;
#else
    alloc_ok = false;
#endif
    prepare_event_driver();
    driver_reset_ptr reset = hal.driver_reset;
    on_report_options_ptr report = grbl.on_report_options;
    initialize_events();
    CHECK(event_details == NULL && hal.driver_reset == reset && grbl.on_report_options == report);
    CHECK(writes == 0 && saves == 0 && warnings == 0);
    run_event_startup();
    CHECK(warnings == 1 && writes == 0 && saves == 0);
    return 0;
}
