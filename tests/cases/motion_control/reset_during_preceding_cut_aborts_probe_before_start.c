#include "support/probe_reset_motion_host.h"

int main(void)
{
    prepare_probe_reset_motion();
    queue_motion_program("G1X1F100");
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_Abort);
    CHECK(reset_sent && sys.abort && driver_resets == 1);
    CHECK(axis_pulses[X_AXIS] >= 10 && axis_pulses[X_AXIS] < 80);
    CHECK(probe_starts == 0 && completed_calls == 0);
    CHECK(sys.probing_state == Probing_Off);
    CHECK(!hal.probe.get_state().is_probing);
    CHECK(!sys.flags.probe_succeeded);
    return EXIT_SUCCESS;
}
