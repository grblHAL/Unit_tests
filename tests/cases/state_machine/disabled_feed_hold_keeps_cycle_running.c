#include "support/hold_host.h"
#include "check.h"

int main(void)
{
    start_hold_move();
    sys.override.control.feed_hold_disable = true;
    CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_CYCLE);
    CHECK(!sys.suspend);
    finish_motion_pulses();
    CHECK(sys.position[X_AXIS] == 1600);
    CHECK(axis_pulses[X_AXIS] == 1600);
    return EXIT_SUCCESS;
}
