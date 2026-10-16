#include "support/spindle_sync_parser_host.h"
int main(void)
{
    prepare_sync_parser();
    CHECK(sync_parser_block("G33Z-1K1") == Status_OK);
    CHECK(axis_pulses[Z_AXIS] == 80 && physical_position[Z_AXIS] == -80);
    CHECK(sys.position[Z_AXIS] == -80 && wake_calls == 1);
    NEAR(gc_state.distance_per_rev, 1);
    CHECK(!sync_parser_driver_running && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
