#include "support/hold_spindle_host.h"
int main(void)
{
    start_spindle_move(true);
    settings.flags.set_rpm_0_during_hold = true;
    hold_motion();
    CHECK(hold_spindle_output_state.on);
    NEAR(hold_spindle_output_rpm, spindle_get(0)->rpm_min);
    NEAR(gc_spindle_get(0)->rpm, 5000);
    int32_t stopped = physical_position[X_AXIS];
    resume_spindle_hold_to_endpoint();
    NEAR(hold_spindle_output_rpm, 5000);
    CHECK(hold_spindle_transition_position == stopped);
    CHECK(!spindle_get(0)->param->option.restore_rpm);
    return EXIT_SUCCESS;
}
