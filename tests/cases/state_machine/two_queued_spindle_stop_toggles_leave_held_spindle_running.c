#include "support/hold_spindle_host.h"
int main(void)
{
    start_spindle_hold(true);
    unsigned calls = hold_spindle_output_calls;
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_STOP));
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_STOP));
    CHECK(protocol_exec_rt_system());
    state_suspend_manager();
    CHECK(hold_spindle_output_state.on);
    CHECK(hold_spindle_output_calls == calls);
    CHECK(sys.override.spindle_stop.value == 0);
    CHECK(state_get() == STATE_HOLD && sys.suspend);
    return EXIT_SUCCESS;
}
