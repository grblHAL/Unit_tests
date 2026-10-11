#include "support/m6_program_host.h"
#include "check.h"

int main(void)
{
    prepare_m6_program();
    m6_atc_state = ATC_Offline;
    CHECK(m6_block("T1M6") == Status_GcodeUnsupportedCommand);
    CHECK(gc_state.tool_pending == 0 && gc_state.tool->tool_id == 0);
    CHECK(m6_change_calls == 0 && m6_select_calls == 0);
    return EXIT_SUCCESS;
}
