#include "support/toolsetter_hook_host.h"
int main(void)
{
    prepare_fixture_probe_hook(ToolChange_Manual_G59_3);
    sys.tlo_reference_set.mask = Z_AXIS_BIT;
    sys.tlo_reference[Z_AXIS] = -320;
    start_manual_change();
    grbl.on_toolchange_ack();
    CHECK(workpiece_touch_off() == Status_OK);
    CHECK(sys.flags.probe_succeeded && gc_state.tool_change);
    CHECK(setter_enable_calls > 0);
    CHECK(tool_stream_handler(CMD_CYCLE_START));
    engine_execute_tasks(STATE_TOOL_CHANGE);
    CHECK(!gc_state.tool_change);
    CHECK(setter_disable_calls > 0);
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    CHECK(tool_stream_handler == original_enqueue);
    return EXIT_SUCCESS;
}
