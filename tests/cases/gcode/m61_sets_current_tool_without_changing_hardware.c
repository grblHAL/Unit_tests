#include "support/m6_program_host.h"
#include "check.h"

int main(void)
{
    prepare_m6_program();
    CHECK(m6_block("M61Q1") == Status_OK);
    CHECK(gc_state.tool == &offset_tool);
    CHECK(m6_change_calls == 0);
    CHECK(m6_select_calls == 1 && !m6_next_selection);
    CHECK(m6_changed_calls == 1 && m6_selected_calls == 1);
    return EXIT_SUCCESS;
}
