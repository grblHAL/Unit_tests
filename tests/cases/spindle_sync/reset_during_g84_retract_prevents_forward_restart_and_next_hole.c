#include "support/tapping_reset_host.h"

static bool retracting_tap(sys_state_t state)
{
    return state == STATE_CYCLE && thread_encoder_state.ccw && physical_position[Z_AXIS] > -60;
}
int main(void)
{
    prepare_tapping_reset();
    thread_reset_condition = retracting_tap;
    (void)sync_parser_block("G91G84X1Z-1R0P0L2F100");
    check_thread_reset_stops_pulses();
    CHECK(sys.position_lost && physical_position[Z_AXIS] > -60 && physical_position[Z_AXIS] < 0);
    CHECK(axis_pulses[Z_AXIS] == (unsigned)(160 + physical_position[Z_AXIS]));
    CHECK(physical_position[X_AXIS] == 880 && axis_pulses[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
