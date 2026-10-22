#include "support/sleep_parking_host.h"
#include "check.h"
static bool requested_start;
static void request_start_during_retract(sys_state_t state)
{
    if(state == STATE_SLEEP && !requested_start &&
       physical_position[Z_AXIS] > -640 && physical_position[Z_AXIS] < -160) {
        requested_start = true;
        CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    }
}

int main(void)
{
    prepare_sleep_parking();
    begin_parking_move();
    hold_motion();
    int32_t held_x = physical_position[X_AXIS];
    unsigned held_pulses = axis_pulses[X_AXIS];
    wait_for_sleep();
    CHECK(sleep_wait_calls == 1 && (sys.rt_exec_state & EXEC_SLEEP));
    grbl.on_execute_realtime = request_start_during_retract;
    finish_sleep_parking();
    CHECK(requested_start);
    CHECK(physical_position[X_AXIS] == held_x && axis_pulses[X_AXIS] == held_pulses);
    CHECK(plan_get_current_block() != NULL);
    return EXIT_SUCCESS;
}
