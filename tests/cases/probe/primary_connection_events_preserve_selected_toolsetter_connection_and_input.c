#include "support/multiple_probe_host.h"
int main(void)
{
    prepare_multiple_probes();
    hal.driver_cap.probe = true;
    CHECK(hal.probe.select(Probe_Toolsetter));
    CHECK(hal.probe.get_state().probe_id == Probe_Toolsetter);
    CHECK(hal.probe.get_state().connected);
    probe_connected_event(NULL);
    CHECK(hal.probe.get_state().probe_id == Probe_Toolsetter);
    CHECK(hal.probe.get_state().connected);
    CHECK(hal.probe.select(Probe_Default));
    probe_connected_event(NULL);
    CHECK(!hal.probe.get_state().connected);
    CHECK(hal.probe.select(Probe_Toolsetter));
    CHECK(hal.probe.get_state().connected);
    probe_inputs[Probe_Toolsetter] = true;
    CHECK(hal.probe.get_state().triggered);
    CHECK(hal.probe.select(Probe_Default));
    probe_connected_event((void *)(uintptr_t)1);
    CHECK(hal.probe.get_state().connected);
    CHECK(!hal.probe.get_state().triggered);
    return EXIT_SUCCESS;
}
