#include "support/macro_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_macro_parser();
    CHECK(macro_block("G66.1P100X12") == Status_OK);
    CHECK(macro_calls == 1);
    CHECK(called_macro == 100);
    NEAR(macro_x, 12);
    NEAR(gc_state.position[X_AXIS], 0);
    CHECK(ngc_call_level() == 0);
    CHECK(macro_block("G67") == Status_OK);
    CHECK(gc_state.g66_args == NULL);
    return EXIT_SUCCESS;
}
