#include "support/probe_irq_host.h"

int main(void)
{
    prepare_probe_irq();
    bool toolsetter = true, second = false;
    CHECK(probe_add(Probe_Toolsetter, 1, IRQ_Mode_None, &toolsetter, irq_read_input));
    CHECK(probe_add(Probe_2, 2, IRQ_Mode_None, &second, irq_read_input));
    CHECK(!hal.probe.is_triggered(Probe_Default));
    CHECK(hal.probe.is_triggered(Probe_Toolsetter));
    CHECK(!hal.probe.is_triggered(Probe_2));
    settings.probe.invert_toolsetter_input = true;
    settings.probe.invert_probe2_input = true;
    CHECK(!hal.probe.is_triggered(Probe_Default));
    CHECK(!hal.probe.is_triggered(Probe_Toolsetter));
    CHECK(hal.probe.is_triggered(Probe_2));
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    CHECK(!hal.probe.is_triggered((probe_id_t)3));
    return EXIT_SUCCESS;
}
