#include "support/toolsetter_hook_host.h"
int main(void)
{
    prepare_fixture_probe_hook(ToolChange_Manual_G59_3);
    start_manual_change();
    grbl.on_toolchange_ack();
    CHECK(hal.probe.get_state().probe_id == Probe_Toolsetter);
    unsigned pulses = axis_pulses[Z_AXIS];
    CHECK(protocol_enqueue_realtime_command(CMD_RESET));
    CHECK(!protocol_exec_rt_system());
    CHECK(!gc_state.tool_change);
    CHECK(reset_calls == 1);
    CHECK(setter_disable_calls > 0);
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    CHECK(tool_stream_handler == original_enqueue);
    CHECK(hal.control.interrupt_callback == original_control);
    CHECK(axis_pulses[Z_AXIS] == pulses && !sys.position_lost);
    return EXIT_SUCCESS;
}
