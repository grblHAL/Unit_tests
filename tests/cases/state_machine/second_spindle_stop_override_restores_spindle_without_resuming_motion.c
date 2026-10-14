#include "support/hold_spindle_host.h"
int main(void)
{
    start_spindle_hold(true);
    unsigned pulses = axis_pulses[X_AXIS];
    toggle_held_spindle();
    toggle_held_spindle();
    CHECK(hold_spindle_output_state.on && !hold_spindle_output_state.ccw);
    NEAR(hold_spindle_output_rpm, 5000);
    CHECK(sys.override.spindle_stop.value == 0);
    CHECK(axis_pulses[X_AXIS] == pulses);
    return EXIT_SUCCESS;
}
