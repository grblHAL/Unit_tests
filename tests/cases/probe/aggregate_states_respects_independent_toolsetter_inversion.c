#include "support/multiple_probe_host.h"

int main(void)
{
    prepare_multiple_probes();
    settings.probe.invert_toolsetter_input = true;
    hal.probe.configure(false, false);
    CHECK(!hal.probe.is_triggered(Probe_Default));
    CHECK(hal.probe.is_triggered(Probe_Toolsetter));
    CHECK(!hal.probe.is_triggered(Probe_2));
    probe_states_t states = probes_get_state();
    CHECK(states.aquired);
    CHECK(!states.probe_triggered);
    CHECK(states.toolsetter_triggered);
    CHECK(!states.probe2_triggered);
    return EXIT_SUCCESS;
}
