#include "support/probe_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_motion();
    CHECK(!hal.probe.get_state().triggered);
    CHECK(probe_to_one_mm((gc_parser_flags_t){.probe_is_away=true}) == GCProbe_FailInit);
    CHECK(sys.alarm == Alarm_ProbeFailInitial);
    CHECK(axis_pulses[X_AXIS] == 0);
    CHECK(completed_calls == 1);
    CHECK(!hal.probe.get_state().is_probing);
    return EXIT_SUCCESS;
}
