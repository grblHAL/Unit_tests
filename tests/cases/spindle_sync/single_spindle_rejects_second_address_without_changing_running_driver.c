#include "support/encoder_thread_motion_host.h"
int main(void)
{
    prepare_encoder_thread_motion();
    CHECK(sync_parser_block("M4S200$1") == Status_GcodeValueOutOfRange);
    CHECK(thread_encoder_state.on && !thread_encoder_state.ccw);
    NEAR(sync_motion_feedback.rpm, 100);
    CHECK(sync_parser_block("M4S200$0") == Status_OK);
    CHECK(thread_encoder_state.on && thread_encoder_state.ccw);
    NEAR(sync_motion_feedback.rpm, 200);
    CHECK(sync_parser_block("M5$0") == Status_OK);
    CHECK(!thread_encoder_state.on);
    NEAR(sync_motion_feedback.rpm, 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
