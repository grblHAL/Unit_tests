#include "support/m6_program_host.h"
int main(void)
{
    prepare_m6_program();
    CHECK(m6_block("T1M6") == Status_OK);
    CHECK(m6_change_calls == 1 && m6_selected_calls == 1);
    CHECK(gc_state.tool->tool_id == 1 && m6_changed_tool == &offset_tool);
    CHECK(!HOST_PARSER_FLAGS.tool_change && state_get() == STATE_IDLE);
    CHECK(m6_block("T2M6") == Status_GcodeIllegalToolTableEntry);
    CHECK(gc_state.tool->tool_id == 1 && m6_change_calls == 1);
    return EXIT_SUCCESS;
}
