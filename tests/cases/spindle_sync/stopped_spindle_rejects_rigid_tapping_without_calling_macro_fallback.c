#include "support/encoder_thread_motion_host.h"
static unsigned fallback_calls;
static status_code_t observe_tapping_fallback(macro_id_t macro, line_number_t line,
                                             parameter_words_t args, uint32_t repeats)
{
    CHECK(macro == 331 && repeats == 1);
    (void)line;
    CHECK(args.i && args.k && args.z);
    fallback_calls++;
    return Status_Unhandled;
}
int main(void)
{
    prepare_encoder_thread_motion();
    grbl.on_macro_execute = observe_tapping_fallback;
    CHECK(sync_parser_block("G33.1Z-1K1I2") == Status_GcodeUnsupportedCommand);
    CHECK(fallback_calls == 0 && ngc_call_level() == 0);
    CHECK(plan_get_current_block() == NULL && sync_encoder_resets == 0);
    CHECK(sync_parser_block("M5") == Status_OK);
    CHECK(!thread_encoder_state.on);
    NEAR(sync_motion_feedback.rpm, 0);
    status_code_t status = sync_parser_block("G33.1Z-1K1I2");
    CHECK(physical_position[X_AXIS] == 800 && physical_position[Z_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL && sync_encoder_resets == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    CHECK(ngc_call_level() == 0);
    CHECK(!sys.override.control.feed_rates_disable && !sys.override.control.spindle_rpm_disable);
    CHECK(!thread_encoder_state.on && !sys.abort && sys.alarm == Alarm_None);
    fprintf(stderr, "Stopped G33.1 status=%u expected=%u macro_fallback_calls=%u\n",
        (unsigned)status, (unsigned)Status_GcodeSpindleNotRunning, fallback_calls);
    CHECK(status == Status_GcodeSpindleNotRunning && fallback_calls == 0);
    return EXIT_SUCCESS;
}
