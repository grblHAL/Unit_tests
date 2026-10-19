#include "support/multi_spindle_hold_motion_host.h"
int main(void)
{
    start_multi_spindle_hold(false);
    unsigned pulses = axis_pulses[X_AXIS];
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_STOP));
    CHECK(protocol_exec_rt_system());
    state_suspend_manager();
    CHECK(!actual_spindle_states[0].on);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_STOP));
    CHECK(protocol_exec_rt_system());
    state_suspend_manager();
    CHECK(actual_spindle_states[0].on);
    NEAR(actual_spindle_rpm[0], 3000);
    CHECK(axis_pulses[X_AXIS] == pulses && state_get() == STATE_HOLD);
    resume_multi_spindle_hold();
    CHECK(spindle_output_calls[1] == 0 && !spindle_is_enabled(1));
    return EXIT_SUCCESS;
}
