#include "support/probe_irq_host.h"

int main(void)
{
    prepare_probe_irq();
    settings.probe.enable_protection = true;
    hal.probe.configure(false, false);
    CHECK(installed_mode == IRQ_Mode_Change);
    hal.probe.connected_toggle();
    CHECK(!hal.probe.get_state().connected);
    CHECK(!hal.probe.get_state().irq_enabled);
    CHECK(!hal.probe.get_caps(Probe_Default).guarded);
    CHECK(installed_mode == IRQ_Mode_None);
    hal.probe.connected_toggle();
    CHECK(hal.probe.get_state().connected);
    CHECK(hal.probe.get_state().irq_enabled);
    CHECK(hal.probe.get_caps(Probe_Default).guarded);
    CHECK(installed_mode == IRQ_Mode_Change);
    return EXIT_SUCCESS;
}
