#include "support/thread_reset_motion_host.h"
static bool cut_is_queued(sys_state_t state)
{
    plan_block_t *last = plan_get_recent_block();
    return state == STATE_IDLE && last && last->target_mm[X_AXIS] == 8.5f && last->target_mm[Z_AXIS] == -.25f;
}
int main(void)
{
    prepare_thread_reset();
    thread_reset_condition = cut_is_queued;
    (void)sync_parser_block("G76Z-2P1I-1J0.5K1E0.25L3H2");
    check_thread_reset_stops_pulses();
    CHECK(!sys.position_lost && sync_encoder_resets == 0);
    CHECK(physical_position[X_AXIS] == 760 && physical_position[Z_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == 40 && axis_pulses[Z_AXIS] == 0);
    plan_block_t *last = plan_get_recent_block();
    CHECK(last != NULL); NEAR(last->target_mm[X_AXIS], 8.5f); NEAR(last->target_mm[Z_AXIS], -.25f);
    return EXIT_SUCCESS;
}
