#include "support/probe_reset_motion_host.h"

int main(void)
{
    prepare_probe_reset_motion();
    CHECK(probe_to_one_mm((gc_parser_flags_t){0}) == GCProbe_Abort);
    CHECK(reset_sent && sys.abort && driver_resets == 1);
    CHECK(probe_starts == 1 && completed_calls == 0);
    CHECK(axis_pulses[X_AXIS] >= 10 && axis_pulses[X_AXIS] < (unsigned)contact_steps);
    CHECK(physical_position[X_AXIS] == sys.position[X_AXIS]);
    CHECK(!sys.flags.probe_succeeded);
    CHECK(sys.position_lost);
    return EXIT_SUCCESS;
}
