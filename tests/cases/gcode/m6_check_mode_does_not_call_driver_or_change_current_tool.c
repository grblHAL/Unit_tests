#include "support/m6_program_host.h"
#include "check.h"

int main(void)
{
    prepare_m6_program();
    tool_data_t *current = gc_state.tool;
    state_set(STATE_CHECK_MODE);
    CHECK(m6_block("T1M6") == Status_OK);
    CHECK(m6_change_calls == 0 && m6_select_calls == 0);
    CHECK(m6_selected_calls == 0 && m6_changed_calls == 0);
    CHECK(gc_state.tool == current && gc_state.tool->tool_id == 0);
    return EXIT_SUCCESS;
}
