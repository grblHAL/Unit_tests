#include "support/thread_reset_motion_host.h"
static bool retract_is_queued(sys_state_t state)
{
    plan_block_t *last = plan_get_recent_block();
    return state == STATE_IDLE && sync_encoder_resets == 1 && last &&
        last->target_mm[X_AXIS] == 10 && last->target_mm[Z_AXIS] == -1;
}
int main(void)
{
    prepare_thread_reset();
    thread_reset_condition = retract_is_queued;
    (void)sync_parser_block("G76Z-1P1I-1J0.5K1");
    fprintf(stderr, "Thread reset: sent=%u abort=%u running=%u encoder=%u position=%ld,%ld pulses=%u,%u state=%u\n",
        reset_sent, sys.abort, sync_parser_driver_running, sync_encoder_resets,
        (long)physical_position[X_AXIS], (long)physical_position[Z_AXIS],
        axis_pulses[X_AXIS], axis_pulses[Z_AXIS], (unsigned)state_get());
    check_thread_reset_stops_pulses();
    CHECK(!sys.position_lost && sync_encoder_resets == 1);
    CHECK(physical_position[X_AXIS] == 680 && physical_position[Z_AXIS] == -80);
    CHECK(axis_pulses[X_AXIS] == 120 && axis_pulses[Z_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0);
    return EXIT_SUCCESS;
}
