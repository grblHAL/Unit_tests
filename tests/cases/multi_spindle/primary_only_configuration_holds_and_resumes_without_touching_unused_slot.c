#include "support/multi_spindle_hold_motion_host.h"
int main(void)
{
    start_multi_spindle_hold(false);
    resume_multi_spindle_hold();
    CHECK(actual_spindle_states[0].on);
    NEAR(actual_spindle_rpm[0], 3000);
    CHECK(spindle_output_calls[1] == 0 && spindle_output_calls[2] == 0);
    return EXIT_SUCCESS;
}
