#include "event_host.h"
int main(void)
{
    load_events();
    bind_event(0, 5);
    bind_event(1, 6);
    bind_event(2, 8);
    grbl.on_state_change(STATE_CYCLE);
    CHECK(!levels[0] && !levels[1] && levels[2]);
    unsigned before = writes;
    grbl.on_state_change(STATE_CYCLE);
    CHECK(writes == before && state_calls == 2);
    grbl.on_state_change(STATE_HOLD);
    CHECK(levels[0] && !levels[1] && !levels[2]);
    grbl.on_state_change(STATE_ALARM);
    CHECK(!levels[0] && levels[1] && !levels[2]);
    hal.driver_reset();
    CHECK(resets == 1 && !levels[0] && levels[1] && !levels[2]);
    grbl.on_state_change(STATE_IDLE);
    CHECK(!levels[0] && !levels[1] && !levels[2]);
    grbl.on_state_change(STATE_HOMING);
    CHECK(levels[2]);
    grbl.on_state_change(STATE_JOG);
    CHECK(levels[2] && state_calls == 7);
    return 0;
}
