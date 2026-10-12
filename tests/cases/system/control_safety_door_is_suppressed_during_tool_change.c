#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq();
    hal.signals_cap.safety_door_ajar = true;
    gc_state.tool_change = true;
    control_interrupt_handler((control_signals_t){.safety_door_ajar=true});
    CHECK(!(sys.rt_exec_state & EXEC_SAFETY_DOOR));
    CHECK(gc_state.tool_change);
    return EXIT_SUCCESS;
}
