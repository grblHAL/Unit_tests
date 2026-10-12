#include "support/probe_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_motion();
    state_set(STATE_CHECK_MODE);
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_CheckMode);
    CHECK(sys.position[X_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == 0);
    CHECK(completed_calls == 0);
    CHECK(!hal.probe.get_state().is_probing);
    return EXIT_SUCCESS;
}
