#include "support/toolsetter_hook_host.h"
int main(void)
{
    prepare_fixture_probe_hook(ToolChange_SemiAutomatic);
    run_automatic_toolsetter();
    CHECK(sys.flags.probe_succeeded && !HOST_PARSER_FLAGS.tool_change);
    CHECK(sys.tlo_reference_set.mask & Z_AXIS_BIT);
    CHECK(sys.probe_position[Z_AXIS] <= -240 && sys.probe_position[Z_AXIS] >= -242);
    CHECK(setter_position_calls > 0 && setter_enable_calls > 0 && setter_disable_calls > 0);
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    CHECK(tool_stream_handler == original_enqueue);
    CHECK(physical_position[Z_AXIS] == -80);
    return EXIT_SUCCESS;
}
