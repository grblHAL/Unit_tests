#include "support/parking_host.h"
#include "check.h"

int main(void)
{
    start_parking_move();
    park_until_retracted();
    int32_t stopped_x = sys.position[X_AXIS];
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_SAFETY_DOOR);
    CHECK(sys.parking_state == Parking_DoorAjar);
    CHECK(!sys.step_control.execute_sys_motion);
    CHECK(sys.position[X_AXIS] == stopped_x);
    CHECK(sys.position[Z_AXIS] == -160);
    CHECK(axis_pulses[Z_AXIS] == 640);
    return EXIT_SUCCESS;
}
