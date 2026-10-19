#include "support/idle_spindle_door_irq_host.h"
int main(void)
{
    prepare_idle_door_spindle(Mode_Standard, true);
    CHECK(!spindle_get(0)->cap.laser);
    unsigned outputs = laser_output_calls;
    open_idle_spindle_door();
    CHECK(protocol_exec_rt_system());
    CHECK(laser_output_state.on && laser_last_driver_level == 500);
    CHECK(laser_output_calls == outputs && state_get() == STATE_IDLE);
    CHECK(!(sys.rt_exec_state & EXEC_SAFETY_DOOR));
    check_idle_door_no_motion();
    return EXIT_SUCCESS;
}
