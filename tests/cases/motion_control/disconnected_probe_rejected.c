#include "support/probe_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_motion();
    hal.probe.connected_toggle();
    CHECK(!hal.probe.get_state().connected);
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_FailInit);
    CHECK(sys.alarm == Alarm_ProbeFailInitial);
    CHECK(axis_pulses[X_AXIS] == 0);
    CHECK(completed_calls == 1);
    return EXIT_SUCCESS;
}
