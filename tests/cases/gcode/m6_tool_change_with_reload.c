#include "support/m6_program_host.h"
static unsigned reload_calls;
static status_code_t reload_table(void) { reload_calls++; return Status_OK; }
int main(void)
{
    prepare_m6_program();
    grbl.tool_table.reload = reload_table;
    CHECK(m6_block("G10L0") == Status_OK && reload_calls == 1);
    CHECK(m6_block("T1M6") == Status_OK && m6_change_calls == 1);
    CHECK(reload_calls == 1 && gc_state.tool->tool_id == 1);
    CHECK(m6_block("G10L0") == Status_ToolInSPindle);
    CHECK(reload_calls == 1);
    return EXIT_SUCCESS;
}
