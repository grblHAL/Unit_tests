#include "support/hold_host.h"
int main(void)
{
    start_hold_move();
    sys.override.feed_rate = 50; sys.override.rapid_rate = 50;
    hold_motion();
    CHECK(sys.override.feed_rate == 50 && sys.override.rapid_rate == 50);
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && physical_position[X_AXIS] == 1600);
    CHECK(sys.override.feed_rate == 50 && sys.override.rapid_rate == 50);
    return EXIT_SUCCESS;
}
