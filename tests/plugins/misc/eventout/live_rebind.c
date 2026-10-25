#include "event_host.h"
int main(void)
{
    load_events();
    bind_event(0, 3);
    hal.coolant.set_state((coolant_state_t){.mist = On});
    CHECK(levels[0]);
    bind_event(0, 4);
    hal.coolant.set_state((coolant_state_t){.mist = On});
    CHECK(!levels[0]);
    hal.coolant.set_state((coolant_state_t){.flood = On});
    CHECK(levels[0]);
    bind_event(0, 0);
    unsigned before = writes;
    hal.coolant.set_state((coolant_state_t){0});
    CHECK(levels[0] && writes == before && coolant_calls == 4);
    grbl.on_report_options(true);
    CHECK(options == 1 && reports == 0);
    grbl.on_report_options(false);
    CHECK(options == 2 && reports == 1);
    return 0;
}
