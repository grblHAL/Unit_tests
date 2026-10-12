#include "support/m6_program_host.h"
#include "check.h"

int main(void)
{
    prepare_m6_program();
    tool_data_t *current = gc_state.tool;
    m6_driver_status = Status_GcodeUnsupportedCommand;
    CHECK(m6_block("T1M6") == Status_GcodeUnsupportedCommand);
    CHECK(m6_change_calls == 1);
    CHECK(gc_state.tool == current && gc_state.tool->tool_id == 0);
    CHECK(gc_state.tool_pending == 1);
    CHECK(m6_changed_calls == 0);
    return EXIT_SUCCESS;
}
