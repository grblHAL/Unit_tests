#include "support/registered_spindle_hold_observer_host.h"
int main(void)
{
    start_registered_spindle_hold();
    toggle_registered_held_spindle();
    int32_t stopped = physical_position[X_AXIS];
    unsigned pulses = axis_pulses[X_AXIS];
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_CYCLE);
    CHECK(held_programmed_calls == 2);
    CHECK(held_programmed_state[1].on && !held_previous_hardware[1].on);
    CHECK(held_programmed_position[1] == stopped);
    NEAR(held_programmed_rpm[1], 500);
    CHECK(laser_output_state.on && axis_pulses[X_AXIS] == pulses);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(sys.position[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    CHECK(axis_pulses[X_AXIS] == 1600);
    return EXIT_SUCCESS;
}
