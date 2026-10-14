#include "support/hold_spindle_host.h"
int main(void)
{
    start_spindle_hold(true);
    unsigned pulses = axis_pulses[X_AXIS];
    toggle_held_spindle();
    CHECK(!hold_spindle_output_state.on);
    NEAR(hold_spindle_output_rpm, 0);
    CHECK(sys.override.spindle_stop.enabled);
    CHECK(gc_spindle_get(0)->state.on);
    NEAR(gc_spindle_get(0)->rpm, 5000);
    CHECK(axis_pulses[X_AXIS] == pulses);
    CHECK(plan_get_current_block() != NULL);
    return EXIT_SUCCESS;
}
