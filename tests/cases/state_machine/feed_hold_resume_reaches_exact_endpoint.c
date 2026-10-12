#include "support/hold_host.h"
#include "check.h"

int main(void)
{
    start_hold_move();
    hold_motion();
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_CYCLE);
    CHECK(!sys.suspend);
    CHECK(wake_calls == 2);
    finish_motion_pulses();
    CHECK(sys.position[X_AXIS] == 1600);
    CHECK(axis_pulses[X_AXIS] == 1600);
    CHECK(plan_get_current_block() == NULL);
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
