#include "support/spindle_sync_parser_host.h"
int main(void)
{
    prepare_sync_parser();
    /* Some encoder drivers expose cumulative counters without a reset hook. */
    hal.spindle_data.reset = NULL;
    spindle_get(0)->reset_data = NULL;
    sync_motion_feedback.angular_position = 10.0f;
    sync_motion_feedback.index_count = 10;
    gc_override_flags_t original = sys.override.control;
    CHECK(sync_parser_block("G33Z1K1") == Status_OK);
    CHECK(wake_calls == 1 && axis_pulses[Z_AXIS] == 80);
    CHECK(physical_position[Z_AXIS] == 80 && sys.position[Z_AXIS] == 80);
    CHECK(sync_encoder_resets == 0 && sync_motion_feedback.index_count >= 12);
    CHECK(sync_angle_reads > 0 && sync_rpm_reads > 0);
    CHECK(sys.override.control.value == original.value);
    CHECK(plan_get_current_block() == NULL && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
