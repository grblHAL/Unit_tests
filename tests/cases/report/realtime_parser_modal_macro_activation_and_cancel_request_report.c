#include "support/parser_change_report_host.h"
static unsigned macro_calls;
static status_code_t modal_macro(macro_id_t id, line_number_t line,
                                parameter_words_t words, uint32_t repeats)
{
    (void)id; (void)line; (void)words; (void)repeats;
    macro_calls++;
    return Status_OK;
}
int main(void)
{
    prepare_parser_change_report();
    grbl.on_macro_execute = modal_macro;
    CHECK(named_parameter_block("G66P100") == Status_OK);
    CHECK(gc_state.g66_args != NULL);
    expect_parser_change_report();
    CHECK(named_parameter_block("G67") == Status_OK);
    CHECK(gc_state.g66_args == NULL);
    expect_parser_change_report();
    CHECK(macro_calls == 0);
    return EXIT_SUCCESS;
}
