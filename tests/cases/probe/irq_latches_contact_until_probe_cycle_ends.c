#include "support/probe_irq_host.h"

int main(void)
{
    prepare_probe_irq();
    hal.probe.configure(false, true);
    CHECK(installed_mode == IRQ_Mode_Rising);
    CHECK(hal.probe.get_state().irq_enabled);
    CHECK(!hal.probe.get_state().triggered);
    CHECK(installed_callback != NULL);
    installed_callback(0, true);
    CHECK(hal.probe.get_state().triggered);
    CHECK(hal.probe.get_state().was_probing);
    CHECK(!irq_input);
    CHECK(control_calls == 0);
    hal.probe.configure(false, false);
    CHECK(installed_mode == IRQ_Mode_None);
    CHECK(!hal.probe.get_state().triggered);
    return EXIT_SUCCESS;
}
