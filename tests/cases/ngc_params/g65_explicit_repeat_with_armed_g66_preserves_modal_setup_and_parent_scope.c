#include "support/macro_parser_host.h"
int main(void)
{
    prepare_macro_parser();
    CHECK(ngc_param_set(24, 99));
    CHECK(macro_block("G66P200X12") == Status_OK);
    CHECK(macro_block("G65P100L1X7") == Status_OK);
    CHECK(macro_calls == 1 && called_macro == 100 && macro_repeats == 1);
    NEAR(macro_x, 7);
    CHECK(macro_block("G0X1") == Status_OK);
    CHECK(macro_calls == 2 && called_macro == 200 && macro_repeats == 1);
    NEAR(macro_x, 12);
    float caller;
    CHECK(ngc_param_get(24, &caller)); NEAR(caller, 99);
    CHECK(ngc_call_level() == 0);
    CHECK(macro_block("G67") == Status_OK && gc_state.g66_args == NULL);
    return EXIT_SUCCESS;
}
