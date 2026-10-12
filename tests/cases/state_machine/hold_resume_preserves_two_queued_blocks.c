#include "support/hold_host.h"
#include "check.h"

int main(void)
{
    start_hold_move();
    char second[] = "G1X30F100";
    CHECK(gc_execute_block(second) == Status_OK);
    hold_motion();
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(sys.position[X_AXIS] == 2400);
    CHECK(axis_pulses[X_AXIS] == 2400);
    CHECK(plan_get_current_block() == NULL);
    CHECK(wake_calls == 2);
    return EXIT_SUCCESS;
}
