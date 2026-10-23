#include "support/encoder_thread_motion_host.h"
#include "support/named_parameter_host.h"
int main(void)
{
    prepare_encoder_thread_motion();
    CHECK(thread_encoder_state.on && !thread_encoder_state.ccw);
    NEAR(read_named_parameter("_spindle_on"), 1);
    NEAR(read_named_parameter("_spindle_cw"), 1);
    CHECK(sync_parser_block("M4S200") == Status_OK);
    CHECK(thread_encoder_state.on && thread_encoder_state.ccw);
    NEAR(sync_motion_feedback.rpm, 200);
    NEAR(read_named_parameter("_spindle_on"), 1);
    NEAR(read_named_parameter("_spindle_cw"), 0);
    CHECK(sync_parser_block("M5") == Status_OK);
    CHECK(!thread_encoder_state.on);
    NEAR(sync_motion_feedback.rpm, 0);
    NEAR(read_named_parameter("_spindle_on"), 0);
    CHECK(sync_parser_block("M3S100") == Status_OK);
    CHECK(thread_encoder_state.on && !thread_encoder_state.ccw);
    NEAR(sync_motion_feedback.rpm, 100);
    NEAR(read_named_parameter("_spindle_on"), 1);
    NEAR(read_named_parameter("_spindle_cw"), 1);
    CHECK(physical_position[X_AXIS] == 800 && physical_position[Y_AXIS] == 0);
    CHECK(physical_position[Z_AXIS] == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
