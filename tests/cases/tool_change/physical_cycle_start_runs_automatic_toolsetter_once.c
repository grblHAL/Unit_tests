#include "support/toolsetter_hook_host.h"

int main(void)
{
    prepare_fixture_probe_hook(ToolChange_SemiAutomatic);
    start_manual_change();
    grbl.on_toolchange_ack();
    unsigned pulses = axis_pulses[Z_AXIS];
    hal.control.interrupt_callback((control_signals_t){.cycle_start = true});
    hal.control.interrupt_callback((control_signals_t){.cycle_start = true});
    CHECK(axis_pulses[Z_AXIS] == pulses && HOST_PARSER_FLAGS.tool_change);
    engine_execute_tasks(STATE_TOOL_CHANGE);
    CHECK(sys.flags.probe_succeeded && !HOST_PARSER_FLAGS.tool_change);
    CHECK(sys.tlo_reference_set.mask & Z_AXIS_BIT);
    CHECK(sys.probe_position[Z_AXIS] <= -240 && sys.probe_position[Z_AXIS] >= -242);
    CHECK(protocol_exec_rt_system());
    CHECK(manual_tool_changed_calls == 1);
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    CHECK(tool_stream_handler == original_enqueue && hal.control.interrupt_callback == original_control);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 240);
    CHECK(physical_position[Z_AXIS] == -80 && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
