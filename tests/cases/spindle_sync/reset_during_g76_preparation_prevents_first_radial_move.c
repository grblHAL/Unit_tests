#include "support/thread_reset_motion_host.h"
static bool thread_preparation_is_idle(sys_state_t state)
{
    return state == STATE_IDLE && sync_encoder_resets == 0 &&
           axis_pulses[X_AXIS] == 0 && axis_pulses[Z_AXIS] == 0;
}
int main(void)
{
    prepare_thread_reset();
    thread_reset_condition = thread_preparation_is_idle;
    (void)sync_parser_block("G76Z-2P1I-1J0.5K1");
    check_thread_reset_stops_pulses();
    CHECK(sync_encoder_resets == 0 && plan_get_current_block() == NULL);
    CHECK(physical_position[X_AXIS] == 800 && physical_position[Z_AXIS] == 0);
    CHECK(!sys.position_lost);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    return EXIT_SUCCESS;
}
