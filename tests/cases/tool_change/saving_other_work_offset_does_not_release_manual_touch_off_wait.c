#include "support/tool_wco_observer_host.h"
int main(void)
{
    prepare_tool_wco_observer();
    install_manual_change_interface();
    tool_wco_block("T3M6");
    tool_wco_block("G10L2P2Z-2");
    CHECK(tool_wco_events == 1 && tool_wco_id == CoordinateSystem_G55);
    grbl.on_toolchange_ack();
    CHECK(tool_stream_handler(CMD_CYCLE_START));
    engine_execute_tasks(STATE_TOOL_CHANGE);
    CHECK(gc_state.tool_change && manual_tool_changed_calls == 0);
    CHECK(state_get() == STATE_TOOL_CHANGE);
    CHECK(axis_pulses[Z_AXIS] == 0);
    tool_wco_block("G10L2P1Z0");
    CHECK(tool_wco_events == 2 && tool_wco_id == CoordinateSystem_G54);
    CHECK(tool_stream_handler(CMD_CYCLE_START));
    engine_execute_tasks(STATE_TOOL_CHANGE);
    CHECK(protocol_execute_realtime());
    CHECK(!gc_state.tool_change && manual_tool_changed_calls == 1);
    CHECK(gc_state.tool->tool_id == 3 && tool_stream_handler == original_enqueue);
    return EXIT_SUCCESS;
}
