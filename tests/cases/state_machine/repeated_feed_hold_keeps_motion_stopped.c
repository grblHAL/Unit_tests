#include "support/hold_host.h"
#include "check.h"

int main(void)
{
    start_hold_move();
    hold_motion();
    int32_t position = sys.position[X_AXIS];
    CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_HOLD);
    CHECK(sys.holding_state == Hold_Complete);
    CHECK(sys.position[X_AXIS] == position);
    CHECK(wake_calls == 1);
    return EXIT_SUCCESS;
}
