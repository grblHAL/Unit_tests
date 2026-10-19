#include "support/incoming_tool_table_host.h"
int main(void)
{
    prepare_incoming_tool_table();
    CHECK(incoming_block("T1") == Status_OK && gc_state.tool_pending == 1);
    CHECK(gc_state.tool->tool_id == 0);
    CHECK(incoming_block("T2") == Status_OK && gc_state.tool_pending == 2);
    CHECK(incoming_block("T5") == Status_GcodeIllegalToolTableEntry);
    CHECK(gc_state.tool_pending == 2 && gc_state.tool->tool_id == 0);
    return EXIT_SUCCESS;
}
