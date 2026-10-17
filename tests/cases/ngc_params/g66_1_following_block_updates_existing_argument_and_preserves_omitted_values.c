#include "support/macro_parser_host.h"
int main(void)
{
    prepare_macro_parser();
    CHECK(macro_block("G66.1P100X12Y8") == Status_OK);
    CHECK(macro_calls == 1);
    status_code_t result = macro_block("X20");
    CHECK(result == Status_OK);
    CHECK(macro_calls == 2 && called_macro == 100);
    NEAR(macro_x, 20);
    NEAR(macro_y, 8);
    CHECK(ngc_call_level() == 0);
    NEAR(gc_state.position[X_AXIS], 0);
    NEAR(gc_state.position[Y_AXIS], 0);
    CHECK(macro_block("G67") == Status_OK);
    CHECK(gc_state.g66_args == NULL);
    return EXIT_SUCCESS;
}
