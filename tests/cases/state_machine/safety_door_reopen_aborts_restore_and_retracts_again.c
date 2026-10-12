#include "support/parking_host.h"
#include "check.h"

int main(void)
{
    start_parking_move();
    park_until_retracted();
    int32_t stopped_x = sys.position[X_AXIS];
    parking_door_open = false;
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned ticks = 0; ticks < 100000 && sys.position[Z_AXIS] > -200; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(protocol_exec_rt_system());
    }
    CHECK(sys.position[Z_AXIS] <= -200);
    CHECK(sys.position[Z_AXIS] > -640);
    CHECK(sys.step_control.execute_sys_motion);
    parking_door_open = true;
    system_set_exec_state_flag(EXEC_SAFETY_DOOR);
    CHECK(protocol_exec_rt_system());
    CHECK(state_door_reopened());
    for(unsigned ticks = 0; ticks < 200000 && sys.parking_state != Parking_DoorAjar; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(protocol_exec_rt_system());
    }
    CHECK(state_get() == STATE_SAFETY_DOOR);
    CHECK(sys.parking_state == Parking_DoorAjar);
    CHECK(sys.position[X_AXIS] == stopped_x);
    CHECK(sys.position[Z_AXIS] == -160);
    CHECK(physical_position[Z_AXIS] == -160);
    CHECK(!sys.step_control.execute_sys_motion);
    CHECK(plan_get_current_block() != NULL);
    return EXIT_SUCCESS;
}
