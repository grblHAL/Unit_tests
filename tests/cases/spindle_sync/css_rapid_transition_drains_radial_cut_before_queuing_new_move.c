#include "support/encoder_thread_motion_host.h"

int main(void)
{
    prepare_encoder_thread_motion();
    CHECK(sync_parser_block("G96S30D1000") == Status_OK);
    CHECK(sync_parser_block("G1X5F100") == Status_OK);
    CHECK(plan_get_current_block() != NULL && physical_position[X_AXIS] == 800);
    CHECK(sync_parser_block("G0X6") == Status_OK);
    CHECK(physical_position[X_AXIS] == 400);
    CHECK(axis_pulses[X_AXIS] == 400);
    CHECK(plan_get_current_block() != NULL);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_CSS);
    CHECK(gc_spindle_get(0)->css == NULL);
    CHECK(thread_encoder_state.on);
    CHECK(sync_motion_feedback.rpm > 0 && sync_motion_feedback.rpm <= 1000);
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[X_AXIS] == 480 && sys.position[X_AXIS] == 480);
    CHECK(axis_pulses[X_AXIS] == 480 && axis_pulses[Z_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL && !sys.abort);
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_CSS);
    return EXIT_SUCCESS;
}
