#include "support/sleep_wait_host.h"
int main(void)
{
    start_sleep_cut();
    sleep_door_open = true;
    CHECK(protocol_enqueue_realtime_command(CMD_SAFETY_DOOR));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(sys.parking_state == Parking_DoorAjar);
    sleep_door_open = false;
    system_set_exec_state_flag(EXEC_DOOR_CLOSED);
    CHECK(protocol_exec_rt_system());
    CHECK(sys.parking_state == Parking_DoorClosed);
    wait_for_sleep();
    CHECK(sleep_wait_calls == 0);
    CHECK(!(sys.rt_exec_state & EXEC_SLEEP));
    CHECK(state_get() == STATE_SAFETY_DOOR);
    return EXIT_SUCCESS;
}
