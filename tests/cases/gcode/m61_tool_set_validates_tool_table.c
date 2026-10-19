#include "support/incoming_tool_table_host.h"
static unsigned selected_tools;
static void tool_changed(tool_data_t *tool) { CHECK(tool != NULL); selected_tools++; }
int main(void)
{
    prepare_incoming_tool_table();
    grbl.tool_table.n_tools = 2;
    hal.control.get_state = incoming_controls;
    hal.stream.is_connected = incoming_connected;
    grbl.on_execute_realtime = protocol_execute_noop;
    grbl.on_tool_changed = tool_changed;
    state_set(STATE_IDLE);
    CHECK(incoming_block("M61Q1") == Status_OK && gc_state.tool->tool_id == 1);
    CHECK(incoming_block("M61Q2") == Status_OK && gc_state.tool->tool_id == 2);
    CHECK(incoming_block("M61Q3") == Status_GcodeIllegalToolTableEntry);
    CHECK(gc_state.tool->tool_id == 2);
    CHECK(selected_tools == 2);
    return EXIT_SUCCESS;
}
