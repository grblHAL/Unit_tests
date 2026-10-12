#include "support/control_irq_host.h"
#include "check.h"

int main(void)
{
    prepare_control_irq();
    CHECK(hal.probe.get_state().connected);
    control_interrupt_handler((control_signals_t){.probe_disconnected=true});
    CHECK(hal.probe.get_state().connected);
    engine_execute_tasks(STATE_IDLE);
    CHECK(!hal.probe.get_state().connected);
    control_interrupt_handler((control_signals_t){.probe_disconnected=true,.deasserted=true});
    CHECK(!hal.probe.get_state().connected);
    engine_execute_tasks(STATE_IDLE);
    CHECK(hal.probe.get_state().connected);
    return EXIT_SUCCESS;
}
