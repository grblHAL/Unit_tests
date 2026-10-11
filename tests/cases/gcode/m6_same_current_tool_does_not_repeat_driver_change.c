#include "support/m6_program_host.h"
#include "check.h"

int main(void)
{
    prepare_m6_program();
    CHECK(m6_block("T1M6") == Status_OK);
    CHECK(m6_block("T1M6") == Status_OK);
    CHECK(m6_change_calls == 1 && m6_changed_calls == 1);
    CHECK(m6_select_calls == 1);
    CHECK(gc_state.tool == &offset_tool);
    return EXIT_SUCCESS;
}
