#include "support/hold_host.h"
#include "check.h"
static bool probe_triggered;
static probe_state_t read_substate_probe(void) { return (probe_state_t){.triggered = probe_triggered}; }

int main(void)
{
    start_hold_move();
    hal.probe.get_state = read_substate_probe;
    CHECK(state_get_substate() == 0);
    probe_triggered = true;
    CHECK(state_get_substate() == 2);
    return EXIT_SUCCESS;
}
