#include "support/registered_spindle_hold_observer_host.h"
int main(void)
{
    start_registered_spindle_hold();
    toggle_registered_held_spindle();
    unsigned pulses = axis_pulses[X_AXIS];
    toggle_registered_held_spindle();
    CHECK(held_programmed_calls == 2 && held_override_calls == 2);
    CHECK(held_programmed_state[1].on && !held_previous_hardware[1].on);
    NEAR(held_programmed_rpm[1], 500);
    CHECK(held_override_hardware[1].on && laser_output_state.on);
    NEAR(laser_output_power, 500);
    CHECK(axis_pulses[X_AXIS] == pulses);
    CHECK(plan_get_current_block() != NULL && sys.suspend);
    return EXIT_SUCCESS;
}
