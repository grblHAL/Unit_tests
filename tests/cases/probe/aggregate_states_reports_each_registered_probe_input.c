#include "support/multiple_probe_host.h"

int main(void)
{
    prepare_multiple_probes();
    probe_inputs[Probe_Default] = true;
    probe_inputs[Probe_Toolsetter] = false;
    probe_inputs[Probe_2] = true;
    probe_states_t states = probes_get_state();
    CHECK(states.aquired);
    CHECK(states.probe_triggered);
    CHECK(!states.toolsetter_triggered);
    CHECK(states.probe2_triggered);
    probe_inputs[Probe_Default] = false;
    probe_inputs[Probe_Toolsetter] = true;
    probe_inputs[Probe_2] = false;
    states = probes_get_state();
    CHECK(!states.probe_triggered && states.toolsetter_triggered && !states.probe2_triggered);
    return EXIT_SUCCESS;
}
