#include "support/toolsetter_hook_host.h"
int main(void)
{
    prepare_fixture_probe_hook(ToolChange_SemiAutomatic);
    setter_hook_contact_z = -16000;
    run_automatic_toolsetter();
    CHECK(!sys.flags.probe_succeeded && !gc_state.tool_change);
    CHECK(setter_enable_calls > 0 && setter_disable_calls > 0);
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    CHECK(tool_stream_handler == original_enqueue);
    CHECK(!(sys.rt_exec_state & EXEC_CYCLE_START));
    return EXIT_SUCCESS;
}
