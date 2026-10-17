#include "support/m6_program_host.h"
static status_code_t change_after_prompt(parser_state_t *parser)
{
    CHECK(strstr(engine_output, "[MSG:Fit drill]" ASCII_EOL) != NULL);
    return m6_driver_change(parser);
}
int main(void)
{
    prepare_m6_program();
    hal.tool.change = change_after_prompt;
    CHECK(m6_block("T1M6(MSG,Fit drill)") == Status_OK);
    CHECK(m6_change_calls == 1 && gc_state.tool == &offset_tool);
    const char *prompt = strstr(engine_output, "[MSG:Fit drill]" ASCII_EOL);
    CHECK(prompt != NULL && strstr(prompt + 1, "[MSG:Fit drill]") == NULL);
    return EXIT_SUCCESS;
}
