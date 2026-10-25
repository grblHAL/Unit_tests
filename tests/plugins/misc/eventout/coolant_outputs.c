#include "event_host.h"
int main(void)
{
    load_events();
    bind_event(0, 3);
    bind_event(1, 4);
    hal.coolant.set_state((coolant_state_t){.mist = On});
    CHECK(levels[0] && !levels[1]);
    hal.coolant.set_state((coolant_state_t){.flood = On});
    CHECK(!levels[0] && levels[1]);
    hal.coolant.set_state((coolant_state_t){.mist = On, .flood = On});
    CHECK(levels[0] && levels[1]);
    hal.coolant.set_state((coolant_state_t){0});
    CHECK(!levels[0] && !levels[1]);
    CHECK(coolant_calls == 4 && writes == 8 && !levels[2] && !levels[3]);
    return 0;
}
