#include "support/sleep_wait_host.h"
int main(void)
{
    start_sleep_cut();
    sleep_door_open = true;
    CHECK(protocol_enqueue_realtime_command(CMD_SAFETY_DOOR));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_SAFETY_DOOR);
    CHECK(sys.parking_state == Parking_DoorAjar);
    unsigned pulses = axis_pulses[X_AXIS];
    wait_for_sleep();
    CHECK(sleep_wait_calls == 1);
    CHECK(sys.rt_exec_state & EXEC_SLEEP);
    CHECK(axis_pulses[X_AXIS] == pulses);
    return EXIT_SUCCESS;
}
