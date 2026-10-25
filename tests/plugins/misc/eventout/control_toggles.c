#include "event_host.h"
int main(void)
{
    load_events();
    bind_event(0, 9);
    bind_event(1, 10);
    bind_event(2, 11);
    CHECK(pending_tasks == 6 && writes == 0);
    run_event_tasks();
    CHECK(!levels[0] && !levels[1] && !levels[2]);
    unsigned before = writes;
    sys.flags.optional_stop_disable = On;
    grbl.on_control_signals_changed((control_signals_t){.stop_disable = On});
    CHECK(pending_tasks == 3 && writes == before && control_calls == 1);
    run_event_tasks();
    CHECK(levels[0] && !levels[1] && !levels[2]);
    sys.flags.single_block = On;
    grbl.on_control_signals_changed((control_signals_t){.single_block = On});
    run_event_tasks();
    CHECK(levels[0] && levels[1] && !levels[2]);
    sys.flags.block_delete_enabled = On;
    grbl.on_control_signals_changed((control_signals_t){.block_delete = On});
    run_event_tasks();
    CHECK(levels[0] && levels[1] && levels[2] && !levels[3]);
    sys.flags.optional_stop_disable = sys.flags.single_block = sys.flags.block_delete_enabled = Off;
    grbl.on_control_signals_changed(
        (control_signals_t){.stop_disable = On, .single_block = On, .block_delete = On});
    run_event_tasks();
    CHECK(!levels[0] && !levels[1] && !levels[2] && control_calls == 4);
    return 0;
}
