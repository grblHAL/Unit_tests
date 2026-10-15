#include "support/hold_host.h"
int main(void)
{
    start_hold_move();
    CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD_LEGACY));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_HOLD && sys.holding_state == Hold_Pending);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(sys.holding_state == Hold_Complete && sys.suspend);
    CHECK(physical_position[X_AXIS] > 0 && physical_position[X_AXIS] < 1600);
    CHECK(plan_get_current_block() != NULL);
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START_LEGACY));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_CYCLE && !sys.suspend);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(sys.position[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    CHECK(axis_pulses[X_AXIS] == 1600);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
