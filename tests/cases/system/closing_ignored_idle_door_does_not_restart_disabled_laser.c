#include "support/idle_spindle_door_irq_host.h"
int main(void)
{
    prepare_idle_door_spindle(Mode_Laser, true);
    open_idle_spindle_door();
    CHECK(!laser_output_state.on);
    unsigned outputs = laser_output_calls;
    idle_door_open = false;
    hal.control.interrupt_callback((control_signals_t){.safety_door_ajar = true, .deasserted = true});
    CHECK(protocol_exec_rt_system());
    CHECK(!laser_output_state.on && laser_last_driver_level == 0);
    CHECK(laser_output_calls == outputs && state_get() == STATE_IDLE);
    check_idle_door_no_motion();
    return EXIT_SUCCESS;
}
