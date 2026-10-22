#include "support/tool_wco_observer_host.h"

int main(void)
{
    prepare_tool_change_motion();
    install_manual_change_interface();
    tool_wco_block("T3M6");
    tool_wco_block("G10L2P1Z0");
    grbl.on_toolchange_ack();
    unsigned pulses = axis_pulses[Z_AXIS];
    hal.control.interrupt_callback((control_signals_t){.cycle_start = true});
    hal.control.interrupt_callback((control_signals_t){.cycle_start = true});
    CHECK(HOST_PARSER_FLAGS.tool_change && axis_pulses[Z_AXIS] == pulses);
    engine_execute_tasks(STATE_TOOL_CHANGE);
    CHECK(!HOST_PARSER_FLAGS.tool_change);
    CHECK(protocol_exec_rt_system());
    CHECK(manual_tool_changed_calls == 1 && gc_state.tool->tool_id == 3);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 240);
    CHECK(physical_position[Z_AXIS] == -80);
    CHECK(plan_get_current_block() == NULL);
    CHECK(tool_stream_handler == original_enqueue && hal.control.interrupt_callback == original_control);
    return EXIT_SUCCESS;
}
