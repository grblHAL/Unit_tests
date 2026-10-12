#include "support/m6_program_host.h"
#include "check.h"

int main(void)
{
    prepare_m6_program();
    offset_entry.name = "End mill";
    m6_expect_named_message = true;
    CHECK(m6_block("T1M6") == Status_OK);
    CHECK(m6_change_calls == 1 && gc_state.tool == &offset_tool);
    CHECK(strstr(engine_output, "[MSG:End mill]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
