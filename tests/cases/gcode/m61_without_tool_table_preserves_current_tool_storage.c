#include "support/m6_program_host.h"
#include "check.h"

int main(void)
{
    prepare_m6_program();
    tool_data_t *current = gc_state.tool;
    grbl.tool_table.n_tools = 0;
    CHECK(m6_block("M61Q1") == Status_OK);
    CHECK(gc_state.tool == current && gc_state.tool->tool_id == 1);
    CHECK(m6_change_calls == 0 && m6_changed_calls == 1);
    CHECK(m6_changed_tool == current);
    return EXIT_SUCCESS;
}
