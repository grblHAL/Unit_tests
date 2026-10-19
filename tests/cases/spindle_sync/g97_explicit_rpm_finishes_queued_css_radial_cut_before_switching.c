#include "support/encoder_thread_motion_host.h"
int main(void)
{
    prepare_encoder_thread_motion();
    CHECK(sync_parser_block("G96S30D1000") == Status_OK);
    CHECK(sync_parser_block("G1X5F100") == Status_OK);
    CHECK(plan_get_current_block() != NULL && physical_position[X_AXIS] == 800);
    CHECK(sync_parser_block("G97S400") == Status_OK);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
    CHECK(physical_position[X_AXIS] == 400 && sys.position[X_AXIS] == 400);
    CHECK(axis_pulses[X_AXIS] == 400 && axis_pulses[Z_AXIS] == 0);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_RPM && gc_spindle_get(0)->css == NULL);
    CHECK(thread_encoder_state.on);
    NEAR(sync_motion_feedback.rpm, 400);
    return EXIT_SUCCESS;
}
