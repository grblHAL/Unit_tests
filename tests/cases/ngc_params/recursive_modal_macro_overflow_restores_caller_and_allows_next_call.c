#include "support/macro_parser_host.h"
static unsigned recursive_calls;
static status_code_t recursive_modal_macro(macro_id_t id, line_number_t line,
    parameter_words_t words, uint32_t repeats)
{
    (void)line;
    if(id != 100 || !words.a || repeats != 1)
        fprintf(stderr, "modal id=%lu A=%u repeats=%lu level=%u\n", (unsigned long)id, (unsigned)words.a, (unsigned long)repeats, (unsigned)ngc_call_level());
    CHECK(id == 100 && words.a && repeats == 1);
    CHECK(++recursive_calls <= 32);
    CHECK(ngc_call_level() == recursive_calls);
    float argument;
    CHECK(ngc_param_get(1, &argument));
    NEAR(argument, 7);
    return macro_block("G66.1P100A7L1");
}
int main(void)
{
    prepare_macro_parser();
    CHECK(ngc_param_set(1, 99));
    grbl.on_macro_execute = recursive_modal_macro;
    CHECK(macro_block("G66.1P100A7L1") == Status_FlowControlStackOverflow);
    CHECK(recursive_calls > 1 && ngc_call_level() == 0);
    CHECK(gc_state.g66_args == NULL);
    float caller;
    CHECK(ngc_param_get(1, &caller));
    NEAR(caller, 99);
    grbl.on_macro_execute = capture_macro;
    CHECK(macro_block("G65P101X3") == Status_OK);
    CHECK(macro_calls == 1 && called_macro == 101 && macro_scope == 1);
    NEAR(macro_x, 3);
    CHECK(ngc_call_level() == 0 && gc_state.g66_args == NULL);
    CHECK(ngc_param_get(1, &caller));
    NEAR(caller, 99);
    return EXIT_SUCCESS;
}
