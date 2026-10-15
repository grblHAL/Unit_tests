#include "support/macro_parser_host.h"

int main(void)
{
    prepare_macro_parser();
    CHECK(macro_block("G66.1P100X12") == Status_OK);
    CHECK(macro_calls == 1);
    NEAR(macro_x, 12);
    status_code_t update_status = macro_block("G66.1X24");
    fprintf(stderr, "G66.1 update status=%u calls=%u\n", (unsigned)update_status, macro_calls);
    CHECK(update_status == Status_OK);
    CHECK(macro_calls == 2 && called_macro == 100);
    NEAR(macro_x, 24);
    CHECK(ngc_call_level() == 0);
    CHECK(macro_block("G67") == Status_OK);
    CHECK(gc_state.g66_args == NULL);
    return EXIT_SUCCESS;
}
