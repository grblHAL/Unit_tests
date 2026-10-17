#include "support/spindle_sync_parser_host.h"
int main(void)
{
    prepare_sync_parser();
    CHECK(sync_parser_block("G33Z1K1") == Status_OK);
    CHECK(physical_position[Z_AXIS] == 80);
    CHECK(sync_parser_block("G33Z2") == Status_OK);
    CHECK(wake_calls == 2 && sync_encoder_resets == 2);
    CHECK(axis_pulses[Z_AXIS] == 160 && physical_position[Z_AXIS] == 160);
    NEAR(gc_state.distance_per_rev, 1);
    CHECK(plan_get_current_block() == NULL && !sync_parser_driver_running);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
