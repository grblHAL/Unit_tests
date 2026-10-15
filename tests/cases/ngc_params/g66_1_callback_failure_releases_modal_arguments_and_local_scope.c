#include "support/macro_parser_host.h"

int main(void)
{
    prepare_macro_parser();
    CHECK(ngc_param_set(24, 99));
    macro_result = Status_InvalidStatement;
    CHECK(macro_block("G66.1P100X12") == Status_InvalidStatement);
    CHECK(macro_calls == 1);
    NEAR(macro_x, 12);
    CHECK(gc_state.g66_args == NULL && ngc_call_level() == 0);
    float restored;
    CHECK(ngc_param_get(24, &restored));
    NEAR(restored, 99);
    return EXIT_SUCCESS;
}
