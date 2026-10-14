#include "support/explicit_probe_program_host.h"
int main(void)
{
    prepare_explicit_probe();
    hal.driver_cap.probe2 = false;
    CHECK(explicit_probe_block("G38.2X1F100P2") == Status_GcodeValueOutOfRange);
    CHECK(wake_calls == 0 && explicit_start_calls == 0 && completed_calls == 0);
    CHECK(explicit_selection_calls == 0 && plan_get_current_block() == NULL);
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    NEAR(gc_state.position[X_AXIS], 0);
    return EXIT_SUCCESS;
}
