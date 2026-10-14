#include "support/hold_spindle_host.h"
int main(void)
{
    start_spindle_move(true);
    unsigned calls = hold_spindle_output_calls;
    CHECK(!settings.flags.set_rpm_0_during_hold);
    hold_motion();
    CHECK(hold_spindle_output_state.on);
    NEAR(hold_spindle_output_rpm, 5000);
    CHECK(hold_spindle_output_calls == calls);
    resume_spindle_hold_to_endpoint();
    CHECK(hold_spindle_output_calls == calls);
    return EXIT_SUCCESS;
}
