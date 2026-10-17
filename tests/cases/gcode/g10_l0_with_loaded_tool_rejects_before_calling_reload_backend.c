#include "support/tool_reload_host.h"
int main(void)
{
    prepare_tool_reload();
    CHECK(m6_block("M61Q1") == Status_OK);
    tool_data_t *selected = gc_state.tool;
    unsigned selections = m6_select_calls;
    CHECK(m6_block("G10L0") == Status_ToolInSPindle);
    CHECK(tool_reload_calls == 0 && gc_state.tool == selected);
    CHECK(gc_state.tool->tool_id == 1 && m6_select_calls == selections);
    CHECK(m6_change_calls == 0);
    return EXIT_SUCCESS;
}
