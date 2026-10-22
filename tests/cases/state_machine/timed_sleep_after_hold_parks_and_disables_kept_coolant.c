#include "support/sleep_parking_host.h"
#include "check.h"

int main(void)
{
    prepare_sleep_parking();
    begin_parking_move();
    hold_motion();
    int32_t held_x = physical_position[X_AXIS];
    unsigned held_x_pulses = axis_pulses[X_AXIS];
    CHECK(held_x > 0 && held_x < 1600);
    wait_for_sleep();
    CHECK(sleep_wait_calls == 1 && (sys.rt_exec_state & EXEC_SLEEP));
    grbl.on_execute_realtime = protocol_execute_noop;
    finish_sleep_parking();
    CHECK(physical_position[X_AXIS] == held_x && axis_pulses[X_AXIS] == held_x_pulses);
    return EXIT_SUCCESS;
}
