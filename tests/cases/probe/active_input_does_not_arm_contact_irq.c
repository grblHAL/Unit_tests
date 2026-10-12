#include "support/probe_irq_host.h"

int main(void)
{
    prepare_probe_irq();
    irq_input = true;
    hal.probe.configure(false, true);
    CHECK(installed_mode == IRQ_Mode_None);
    CHECK(!hal.probe.get_state().irq_enabled);
    CHECK(hal.probe.get_state().triggered);
    irq_input = false;
    CHECK(!hal.probe.get_state().triggered);
    return EXIT_SUCCESS;
}
