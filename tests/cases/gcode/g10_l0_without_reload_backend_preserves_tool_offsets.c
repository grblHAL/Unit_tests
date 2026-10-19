#include "support/tool_reload_host.h"
int main(void)
{
    prepare_tool_reload();
    CHECK(m6_block("G43.1Z5") == Status_OK);
    grbl.tool_table.reload = NULL;
    CHECK(m6_block("G10L0") == Status_GcodeUnsupportedCommand);
    CHECK(tool_reload_calls == 0 && gc_state.tool->tool_id == 0);
    CHECK(gc_state.modal.tool_length_offset[Z_AXIS] == 5);
    CHECK(m6_change_calls == 0 && m6_select_calls == 0);
    return EXIT_SUCCESS;
}
