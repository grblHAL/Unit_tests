#include "support/encoder_thread_motion_host.h"
int main(void)
{
    prepare_encoder_thread_motion();
    CHECK(sync_parser_block("G20G76Z-0.05P0.01I-0.04J0.02K0.04") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    NEAR(gc_state.distance_per_rev, .254f);
    CHECK(sync_encoder_resets == 2);
    CHECK(physical_position[X_AXIS] == 800 && physical_position[Z_AXIS] == -102);
    CHECK(axis_pulses[X_AXIS] == 570 && axis_pulses[Z_AXIS] == 306);
    CHECK(plan_get_current_block() == NULL && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
