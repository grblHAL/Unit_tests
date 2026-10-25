#include "support/thread_reset_motion_host.h"
static bool final_cut_finished(sys_state_t state)
{
    return state == STATE_IDLE && sync_encoder_resets == 2 &&
        physical_position[X_AXIS] == 640 && physical_position[Z_AXIS] == -80;
}
int main(void)
{
    prepare_thread_reset();
    thread_reset_condition = final_cut_finished;
    (void)sync_parser_block("G76Z-1P1I-1J0.5K1");
    fprintf(stderr, "Thread reset: sent=%u abort=%u running=%u encoder=%u position=%ld,%ld pulses=%u,%u state=%u\n",
        reset_sent, sys.abort, sync_parser_driver_running, sync_encoder_resets,
        (long)physical_position[X_AXIS], (long)physical_position[Z_AXIS],
        axis_pulses[X_AXIS], axis_pulses[Z_AXIS], (unsigned)state_get());
    check_thread_reset_stops_pulses();
    CHECK(!sys.position_lost && sync_encoder_resets == 2);
    CHECK(physical_position[X_AXIS] == 640 && physical_position[Z_AXIS] == -80);
    CHECK(axis_pulses[X_AXIS] == 400 && axis_pulses[Z_AXIS] == 240);
    CHECK(axis_pulses[Y_AXIS] == 0);
    return EXIT_SUCCESS;
}
