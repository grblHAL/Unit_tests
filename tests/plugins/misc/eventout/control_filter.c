#include "event_host.h"
int main(void)
{
    load_events();
    bind_event(0, 9);
    run_event_tasks();
    unsigned before = writes;
    grbl.on_control_signals_changed((control_signals_t){.cycle_start = On});
    CHECK(control_calls == 1 && pending_tasks == 0 && writes == before);
    sys.flags.optional_stop_enable = On;
    grbl.on_control_signals_changed((control_signals_t){.stop_enable = On});
    CHECK(pending_tasks == 1 && writes == before);
    bind_event(0, 0);
    run_event_tasks();
    CHECK(!levels[0] && writes == before && control_calls == 2);
    return 0;
}
