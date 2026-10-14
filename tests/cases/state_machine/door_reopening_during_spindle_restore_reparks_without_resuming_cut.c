#include "support/parking_accessory_host.h"
int main(void)
{
    start_powered_parking_move(false);
    park_until_retracted();
    int32_t stopped_x = physical_position[X_AXIS];
    settings.safety_door.spindle_on_delay = 0.1f;
    parking_reopen_on_restore = true;
    close_and_resume_parking();
    for(unsigned ticks = 0; ticks < 200000 && sys.parking_state != Parking_DoorAjar; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(protocol_exec_rt_system());
    }
    CHECK(!parking_reopen_on_restore && parking_door_open);
    CHECK(state_get() == STATE_SAFETY_DOOR && sys.parking_state == Parking_DoorAjar);
    CHECK(!parking_spindle_state.on && !parking_coolant.flood);
    CHECK(physical_position[X_AXIS] == stopped_x && physical_position[Z_AXIS] == -160);
    CHECK(!sys.step_control.execute_sys_motion && plan_get_current_block() != NULL);
    return EXIT_SUCCESS;
}
