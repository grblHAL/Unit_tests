#include "support/encoder_thread_motion_host.h"
int main(void)
{
    prepare_encoder_thread_motion();
    CHECK(sync_parser_block("M5") == Status_OK);
    CHECK(!thread_encoder_state.on);
    NEAR(sync_motion_feedback.rpm, 0);
    CHECK(sync_parser_block("G76Z-1P1I-1J0.5K1") == Status_GcodeSpindleNotRunning);
    CHECK(physical_position[X_AXIS] == 800 && physical_position[Z_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL && sync_encoder_resets == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    CHECK(!thread_encoder_state.on && !sys.abort && sys.alarm == Alarm_None);
    CHECK(sync_parser_block("M3S100") == Status_OK);
    CHECK(sync_parser_block("G76Z-1P1I-1J0.5K1") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[X_AXIS] == 800 && physical_position[Z_AXIS] == -80);
    CHECK(axis_pulses[X_AXIS] == 560 && axis_pulses[Z_AXIS] == 240);
    CHECK(axis_pulses[Y_AXIS] == 0 && sync_encoder_resets == 2);
    CHECK(plan_get_current_block() == NULL && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
