#include "support/hold_host.h"
#include "check.h"

int main(void)
{
    start_hold_move();
    CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_HOLD);
    CHECK(state_get_substate() == 1);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_HOLD);
    CHECK(state_get_substate() == 0);
    CHECK(sys.position[X_AXIS] > 0 && sys.position[X_AXIS] < 1600);
    return EXIT_SUCCESS;
}
