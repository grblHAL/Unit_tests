#include "support/thread_reset_motion_host.h"
static bool radial_approach_finished(sys_state_t state)
{
    return state == STATE_IDLE && physical_position[X_AXIS] == 760 && sync_encoder_resets == 0;
}
int main(void)
{
    prepare_thread_reset();
    thread_reset_condition = radial_approach_finished;
    (void)sync_parser_block("G76Z-2P1I-1J0.5K1E0.25L1H2");
    check_thread_reset_stops_pulses();
    CHECK(!sys.position_lost && sync_encoder_resets == 0);
    CHECK(physical_position[X_AXIS] == 760 && physical_position[Z_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == 40 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
