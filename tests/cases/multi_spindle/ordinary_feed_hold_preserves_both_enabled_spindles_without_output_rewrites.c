#include "support/multi_spindle_hold_motion_host.h"
int main(void)
{
    start_multi_spindle_hold(true);
    unsigned primary = spindle_output_calls[0], secondary = spindle_output_calls[1];
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    NEAR(actual_spindle_rpm[1], 7000);
    resume_multi_spindle_hold();
    CHECK(actual_spindle_states[0].on && actual_spindle_states[1].on);
    NEAR(actual_spindle_rpm[0], 3000);
    NEAR(actual_spindle_rpm[1], 7000);
    CHECK(spindle_output_calls[0] == primary && spindle_output_calls[1] == secondary);
    return EXIT_SUCCESS;
}
