#include "support/tapping_reset_host.h"

static bool cutting_tap(sys_state_t state)
{
    return state == STATE_CYCLE && physical_position[Z_AXIS] < -20;
}
int main(void)
{
    prepare_tapping_reset();
    thread_reset_condition = cutting_tap;
    (void)sync_parser_block("G84Z-1R0P0F100");
    check_thread_reset_stops_pulses();
    CHECK(sys.position_lost && physical_position[Z_AXIS] > -80);
    CHECK(physical_position[Z_AXIS] < -20);
    CHECK(axis_pulses[Z_AXIS] == (unsigned)-physical_position[Z_AXIS]);
    CHECK(physical_position[X_AXIS] == 800 && axis_pulses[X_AXIS] == 0);
    return EXIT_SUCCESS;
}
