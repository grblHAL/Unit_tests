#include "support/probe_irq_host.h"

int main(void)
{
    prepare_probe_irq();
    irq_accept = false;
    hal.probe.configure(false, true);
    CHECK(!hal.probe.get_state().irq_enabled);
    CHECK(!hal.probe.get_state().triggered);
    irq_input = true;
    CHECK(hal.probe.get_state().triggered);
    irq_input = false;
    CHECK(!hal.probe.get_state().triggered);
    return EXIT_SUCCESS;
}
