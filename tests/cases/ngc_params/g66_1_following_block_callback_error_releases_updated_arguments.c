#include "support/macro_parser_host.h"
int main(void)
{
    prepare_macro_parser();
    CHECK(ngc_param_set(24, 99));
    CHECK(macro_block("G66.1P100X12Y8") == Status_OK);
    macro_result = Status_InvalidStatement;
    status_code_t result = macro_block("X20");
    CHECK(result == Status_InvalidStatement);
    CHECK(macro_calls == 2);
    NEAR(macro_x, 20);
    CHECK(gc_state.g66_args == NULL && ngc_call_level() == 0);
    float restored;
    CHECK(ngc_param_get(24, &restored));
    NEAR(restored, 99);
    NEAR(gc_state.position[X_AXIS], 0);
    return EXIT_SUCCESS;
}
