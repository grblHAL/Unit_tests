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
    // Contact bounce must not clear the first hit or become an idle control IRQ.
    for(unsigned bounce = 0; bounce < 4; bounce++) {
        irq_input = false; // Release has no callback on a rising-edge IRQ.
        CHECK(hal.probe.get_state().triggered);
        irq_input = true;
        installed_callback(0, true);
        CHECK(hal.probe.get_state().triggered);
        CHECK(hal.probe.get_state().was_probing);
        CHECK(hal.probe.get_state().is_probing);
        CHECK(control_calls == 0);
    }
    irq_input = false;
    hal.probe.configure(false, false);
    CHECK(installed_mode == IRQ_Mode_None);
    CHECK(!hal.probe.get_state().triggered);
    hal.probe.configure(false, true);
    CHECK(installed_mode == IRQ_Mode_Rising);
    CHECK(!hal.probe.get_state().triggered && !hal.probe.get_state().was_probing);
    irq_input = true;
    installed_callback(0, true);
    CHECK(hal.probe.get_state().triggered && hal.probe.get_state().was_probing);
    CHECK(control_calls == 0);
    hal.probe.configure(false, false);
    CHECK(installed_mode == IRQ_Mode_None);
    return EXIT_SUCCESS;
}
