#include "support/engine_host.h"
#include "probe.h"
#include "check.h"
static bool read_input(void *input) { return *(bool *)input; }
int main(void)
{
    engine_prepare();
    bool toolsetter = true, secondary = false;
    CHECK(probe_add(Probe_Toolsetter, 0, IRQ_Mode_None, &toolsetter, read_input));
    CHECK(probe_add(Probe_2, 1, IRQ_Mode_None, &secondary, read_input));
    hal.probe.configure(false, false);
    CHECK(hal.probe.get_state().probe_id == Probe_Toolsetter);
    CHECK(hal.probe.get_state().triggered);
    CHECK(!hal.probe.get_caps(Probe_Default).available);
    CHECK(!hal.probe.is_triggered(Probe_Default));
    CHECK(!hal.probe.select(Probe_Default));
    CHECK(hal.probe.get_state().probe_id == Probe_Toolsetter);
    CHECK(hal.probe.get_state().triggered);
    CHECK(hal.probe.select(Probe_2));
    CHECK(!hal.probe.get_state().triggered);
    secondary = true;
    CHECK(hal.probe.get_state().triggered && hal.probe.is_triggered(Probe_2));
    probe_states_t states = probes_get_state();
    CHECK(states.aquired && states.toolsetter_triggered && states.probe2_triggered);
    CHECK(!states.probe_triggered);
    CHECK(hal.probe.select(Probe_Toolsetter));
    CHECK(hal.probe.get_state().probe_id == Probe_Toolsetter);
    return EXIT_SUCCESS;
}
