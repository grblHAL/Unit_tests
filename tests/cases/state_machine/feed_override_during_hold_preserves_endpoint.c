#include "support/hold_host.h"
#include "check.h"

int main(void)
{
    start_hold_move();
    hold_motion();
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_FEED_COARSE_PLUS));
    CHECK(protocol_exec_rt_system());
    CHECK(sys.override.feed_rate == 110);
    CHECK(state_get() == STATE_HOLD);
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(sys.position[X_AXIS] == 1600);
    CHECK(axis_pulses[X_AXIS] == 1600);
    CHECK(wake_calls == 2);
    return EXIT_SUCCESS;
}
