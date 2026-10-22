#include "support/thread_reset_motion_host.h"
static bool first_cut(sys_state_t state)
{
    return state == STATE_CYCLE && sync_encoder_resets == 1 && physical_position[Z_AXIS] <= -20;
}
int main(void)
{
    prepare_thread_reset();
    thread_reset_condition = first_cut;
    (void)sync_parser_block("G76Z-1P1I-1J0.5K1H2");
    check_thread_reset_stops_pulses();
    CHECK(sys.position_lost && sync_encoder_resets == 1);
    CHECK(physical_position[Z_AXIS] <= -20 && physical_position[Z_AXIS] >= -80);
    return EXIT_SUCCESS;
}
