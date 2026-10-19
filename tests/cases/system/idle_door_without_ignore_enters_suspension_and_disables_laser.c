#include "support/idle_spindle_door_irq_host.h"
int main(void)
{
    prepare_idle_door_spindle(Mode_Laser, false);
    open_idle_spindle_door();
    CHECK(sys.rt_exec_state & EXEC_SAFETY_DOOR);
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_SAFETY_DOOR && sys.suspend);
    CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    check_idle_door_no_motion();
    return EXIT_SUCCESS;
}
