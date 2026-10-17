#include "support/m6_program_host.h"
int main(void)
{
    prepare_m6_program();
    CHECK(m6_block("T1M6") == Status_OK);
    CHECK(m6_change_calls == 1);
    engine_output[0] = '\0';
    CHECK(m6_block("T1M6(MSG,Check fitted tool)") == Status_OK);
    CHECK(strstr(engine_output, "[MSG:Check fitted tool]" ASCII_EOL) != NULL);
    CHECK(m6_change_calls == 1 && gc_state.tool == &offset_tool);
    return EXIT_SUCCESS;
}
