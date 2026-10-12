#include "support/probe_irq_host.h"

int main(void)
{
    prepare_probe_irq();
    hal.driver_cap.probe = true;
    probe_connected_event(NULL);
    CHECK(!hal.probe.get_state().connected);
    probe_connected_event((void *)(uintptr_t)1);
    CHECK(hal.probe.get_state().connected);
    probe_connected_event((void *)(uintptr_t)1);
    CHECK(hal.probe.get_state().connected);
    hal.driver_cap.probe = false;
    probe_connected_event(NULL);
    CHECK(hal.probe.get_state().connected);
    probe_connected_event((void *)(uintptr_t)2);
    CHECK(!hal.probe.get_state().connected);
    return EXIT_SUCCESS;
}
