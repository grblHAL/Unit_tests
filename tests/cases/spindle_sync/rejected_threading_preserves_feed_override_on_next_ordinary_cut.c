#include "support/encoder_thread_motion_host.h"
int main(void)
{
    prepare_encoder_thread_motion();
    CHECK(sync_parser_block("M48M5") == Status_OK);
    CHECK(sync_parser_block("G76Z-1P1I-1J0.5K1") == Status_GcodeSpindleNotRunning);
    CHECK(sync_encoder_resets == 0 && plan_get_current_block() == NULL);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_FEED_COARSE_PLUS));
    CHECK(protocol_exec_rt_system());
    CHECK(sys.override.feed_rate == 110);
    CHECK(sync_parser_block("G1X11F100") == Status_OK);
    plan_block_t *cut = plan_get_current_block();
    CHECK(cut != NULL);
    fprintf(stderr, "After rejected G76: feed override=%u, next cut no_feed_override=%u, runtime disabled=%u\n",
        (unsigned)sys.override.feed_rate, (unsigned)cut->condition.no_feed_override,
        (unsigned)sys.override.control.feed_rates_disable);
    CHECK(!cut->condition.no_feed_override);
    CHECK(protocol_buffer_synchronize());
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 880);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
