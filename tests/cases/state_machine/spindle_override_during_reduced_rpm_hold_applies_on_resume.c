#include "support/hold_spindle_host.h"
int main(void)
{
    start_spindle_move(true);
    settings.flags.set_rpm_0_during_hold = true;
    hold_motion();
    unsigned pulses = axis_pulses[X_AXIS];
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_COARSE_PLUS));
    CHECK(protocol_exec_rt_system());
    state_suspend_manager();
    CHECK(spindle_get(0)->param->override_pct == 110);
    NEAR(hold_spindle_output_rpm, spindle_get(0)->rpm_min);
    CHECK(axis_pulses[X_AXIS] == pulses);
    resume_spindle_hold_to_endpoint();
    NEAR(hold_spindle_output_rpm, 5500);
    NEAR(gc_spindle_get(0)->rpm, 5000);
    return EXIT_SUCCESS;
}
