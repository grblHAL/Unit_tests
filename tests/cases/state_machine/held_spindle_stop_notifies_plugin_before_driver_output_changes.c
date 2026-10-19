#include "support/registered_spindle_hold_observer_host.h"
int main(void)
{
    start_registered_spindle_hold();
    unsigned pulses = axis_pulses[X_AXIS];
    toggle_registered_held_spindle();
    CHECK(held_programmed_calls == 1 && held_override_calls == 1);
    CHECK(!held_programmed_state[0].on && held_previous_hardware[0].on);
    NEAR(held_programmed_rpm[0], 0);
    CHECK(!held_override_hardware[0].on && !laser_output_state.on);
    CHECK(axis_pulses[X_AXIS] == pulses && plan_get_current_block() != NULL);
    return EXIT_SUCCESS;
}
