#include "support/spindle_sync_parser_host.h"
int main(void)
{
    prepare_sync_parser();
    gc_override_flags_t original = sys.override.control;
    CHECK(sync_parser_block("G93G33Z1K1") == Status_OK);
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime);
    NEAR(gc_state.distance_per_rev, 1);
    CHECK(physical_position[Z_AXIS] == 80 && axis_pulses[Z_AXIS] == 80);
    CHECK(sync_encoder_resets == 1 && sync_angle_reads > 0);
    CHECK(sys.override.control.value == original.value);
    CHECK(sync_parser_block("G1Z2") == Status_GcodeUndefinedFeedRate);
    CHECK(gc_state.position[Z_AXIS] == 1 && physical_position[Z_AXIS] == 80);
    CHECK(plan_get_current_block() == NULL && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
