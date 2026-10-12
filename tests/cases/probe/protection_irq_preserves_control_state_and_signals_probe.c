#include "support/probe_irq_host.h"

int main(void)
{
    prepare_probe_irq();
    settings.probe.enable_protection = true;
    hal.probe.configure(false, false);
    CHECK(installed_mode == IRQ_Mode_Change);
    CHECK(hal.probe.get_caps(Probe_Default).guarded);
    installed_callback(0, true);
    CHECK(control_calls == 1);
    CHECK(captured_control.feed_hold);
    CHECK(captured_control.probe_triggered);
    CHECK(!hal.probe.get_state().is_probing);
    return EXIT_SUCCESS;
}
