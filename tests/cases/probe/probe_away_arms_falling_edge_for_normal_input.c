#include "support/probe_irq_host.h"

int main(void)
{
    prepare_probe_irq();
    irq_input = true;
    hal.probe.configure(true, true);
    CHECK(installed_mode == IRQ_Mode_Falling);
    CHECK(hal.probe.get_state().inverted);
    CHECK(!hal.probe.get_state().triggered);
    installed_callback(0, false);
    CHECK(hal.probe.get_state().triggered);
    CHECK(control_calls == 0);
    return EXIT_SUCCESS;
}
