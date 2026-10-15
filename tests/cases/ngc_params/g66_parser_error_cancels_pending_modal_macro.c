#include "support/macro_parser_host.h"

int main(void)
{
    prepare_macro_parser();
    CHECK(macro_block("G66P100X12") == Status_OK);
    CHECK(gc_state.g66_args != NULL && macro_calls == 0);
    CHECK(macro_block("G999") == Status_GcodeUnsupportedCommand);
    CHECK(gc_state.g66_args == NULL);
    CHECK(macro_block("G0X1") == Status_OK);
    CHECK(macro_calls == 0 && ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
