#include "support/engine_host.h"
#include "probe.h"
#include "check.h"
static bool read_input(void *input) { return *(bool *)input; }
int main(void)
{
    engine_prepare();
    bool toolsetter = true, primary = false;
    CHECK(probe_add(Probe_Toolsetter, 0, IRQ_Mode_None, &toolsetter, read_input));
    hal.probe.configure(false, false);
    CHECK(hal.probe.get_state().probe_id == Probe_Toolsetter);
    CHECK(hal.probe.get_state().triggered);
    CHECK(probe_add(Probe_Default, 1, IRQ_Mode_None, &primary, read_input));
    hal.probe.configure(false, false);
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    CHECK(!hal.probe.get_state().triggered);
    CHECK(hal.probe.get_caps(Probe_Default).available && hal.probe.get_caps(Probe_Toolsetter).available);
    CHECK(hal.probe.is_triggered(Probe_Toolsetter) && !hal.probe.is_triggered(Probe_Default));
    primary = true;
    CHECK(hal.probe.get_state().triggered);
    probe_states_t states = probes_get_state();
    CHECK(states.aquired && states.probe_triggered && states.toolsetter_triggered);
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    CHECK(hal.probe.select(Probe_Toolsetter));
    toolsetter = false;
    CHECK(!hal.probe.get_state().triggered);
    CHECK(hal.probe.is_triggered(Probe_Default));
    CHECK(hal.probe.select(Probe_Default));
    CHECK(hal.probe.get_state().triggered);
    return EXIT_SUCCESS;
}
