#include "support/idle_spindle_door_irq_host.h"
int main(void)
{
    prepare_idle_door_spindle(Mode_Laser, true);
    unsigned outputs = laser_output_calls;
    open_idle_spindle_door();
    CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    CHECK(laser_output_calls == outputs + 1);
    CHECK(!(sys.rt_exec_state & EXEC_SAFETY_DOOR) && state_get() == STATE_IDLE);
    check_idle_door_no_motion();
    return EXIT_SUCCESS;
}
