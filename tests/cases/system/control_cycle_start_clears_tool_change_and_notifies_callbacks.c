#include "support/control_irq_host.h"
#include "check.h"
static unsigned start_calls;
static void cycle_started(void) { CHECK(!gc_state.tool_change); CHECK(control_change_calls == 1); start_calls++; }
int main(void)
{
    prepare_control_irq();
    hal.signals_cap.cycle_start = true;
    grbl.on_cycle_start = cycle_started;
    gc_state.tool_change = true;
    control_interrupt_handler((control_signals_t){.cycle_start=true});
    CHECK(sys.rt_exec_state & EXEC_CYCLE_START);
    CHECK(!gc_state.tool_change);
    CHECK(control_change_calls == 1);
    CHECK(changed_controls.cycle_start);
    CHECK(start_calls == 1);
    return EXIT_SUCCESS;
}
