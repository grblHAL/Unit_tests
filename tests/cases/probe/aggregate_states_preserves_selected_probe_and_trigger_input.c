#include "support/multiple_probe_host.h"

int main(void)
{
    prepare_multiple_probes();
    probe_inputs[Probe_Default] = false;
    probe_inputs[Probe_2] = true;
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    CHECK(!hal.probe.get_state().triggered);
    probe_states_t states = probes_get_state();
    CHECK(states.aquired && states.probe2_triggered);
    probe_state_t selected = hal.probe.get_state();
    fprintf(stderr, "selected probe after aggregate read: %u, triggered=%u\n",
            (unsigned)selected.probe_id, (unsigned)selected.triggered);
    CHECK(selected.probe_id == Probe_Default);
    CHECK(!selected.triggered);
    return EXIT_SUCCESS;
}
