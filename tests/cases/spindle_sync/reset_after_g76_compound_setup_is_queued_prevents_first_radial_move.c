#include "support/thread_reset_motion_host.h"
static bool compound_setup_seen;
static bool compound_setup_is_queued(sys_state_t state)
{
    plan_block_t *block = plan_get_current_block();
    if(state != STATE_IDLE || block == NULL || sync_encoder_resets != 0)
        return false;
    CHECK(!sync_parser_driver_running && block->condition.rapid_motion);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    compound_setup_seen = true;
    return true;
}
int main(void)
{
    prepare_thread_reset();
    thread_reset_condition = compound_setup_is_queued;
    (void)sync_parser_block("G76Z-2P1I-1J0.5K1Q29");
    CHECK(compound_setup_seen);
    check_thread_reset_stops_pulses();
    CHECK(sync_encoder_resets == 0 && !sys.position_lost);
    CHECK(physical_position[X_AXIS] == 800 && physical_position[Z_AXIS] == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    return EXIT_SUCCESS;
}
