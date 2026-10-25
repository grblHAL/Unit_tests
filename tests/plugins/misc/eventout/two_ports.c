#include "event_host.h"
static unsigned visits;
static bool visit(const setting_detail_t *setting, uint_fast16_t offset, void *data)
{
    CHECK(setting == event_details->settings && data == &visits && offset == visits);
    visits++;
    return true;
}
int main(void)
{
    available_ports = 2;
    load_events();
    CHECK(event_details->iterator(event_details->settings, visit, &visits) && visits == 2);
    CHECK(event_details->settings->is_available(event_details->settings, 1));
    CHECK(!event_details->settings->is_available(event_details->settings, 2));
    bind_event(0, 3);
    bind_event(1, 4);
    hal.coolant.set_state((coolant_state_t){.mist = On});
    CHECK(levels[0] && !levels[1]);
    hal.coolant.set_state((coolant_state_t){.flood = On});
    CHECK(!levels[0] && levels[1]);
    hal.driver_reset();
    CHECK(!levels[0] && !levels[1] && resets == 1);
    CHECK(writes == 6 && !levels[2] && !levels[3]);
    return 0;
}
