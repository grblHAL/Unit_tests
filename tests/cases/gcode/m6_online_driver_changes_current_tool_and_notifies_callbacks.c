#include "support/m6_program_host.h"
#include "check.h"

int main(void)
{
    prepare_m6_program();
    CHECK(m6_block("T1M6") == Status_OK);
    CHECK(m6_change_calls == 1 && m6_select_calls == 1);
    CHECK(m6_next_selection && m6_driver_selected_tool == &offset_tool);
    CHECK(m6_selected_calls == 1 && m6_selected_tool == &offset_tool);
    CHECK(m6_changed_calls == 1 && m6_changed_tool == &offset_tool);
    CHECK(gc_state.tool == &offset_tool && gc_state.tool_pending == 1);
    CHECK(hal.stream.report.flags.value & Report_Tool);
    return EXIT_SUCCESS;
}
