#include "support/sleep_wait_host.h"
int main(void)
{
    start_sleep_cut();
    CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    CHECK(protocol_exec_rt_system());
    CHECK(sys.holding_state == Hold_Pending);
    wait_for_sleep();
    CHECK(sleep_wait_calls == 0);
    CHECK(!(sys.rt_exec_state & EXEC_SLEEP));
    CHECK(state_get() == STATE_HOLD);
    return EXIT_SUCCESS;
}
