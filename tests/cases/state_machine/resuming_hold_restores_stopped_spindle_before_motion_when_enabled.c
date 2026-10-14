#include "support/hold_spindle_host.h"
int main(void)
{
    start_spindle_hold(true);
    toggle_held_spindle();
    int32_t stopped = physical_position[X_AXIS];
    resume_spindle_hold_to_endpoint();
    CHECK(hold_spindle_output_state.on);
    NEAR(hold_spindle_output_rpm, 5000);
    CHECK(hold_spindle_transition_position == stopped);
    CHECK(gc_spindle_get(0)->state.on);
    CHECK(sys.override.spindle_stop.value == 0);
    return EXIT_SUCCESS;
}
