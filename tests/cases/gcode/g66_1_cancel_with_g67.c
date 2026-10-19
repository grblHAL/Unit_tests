#include "support/incoming_macro_host.h"
int main(void)
{
    prepare_incoming_macro();
    CHECK(incoming_block("G66.1P100X12Y8") == Status_OK);
    CHECK(macro_calls == 1);
    CHECK(incoming_block("X20") == Status_OK);
    CHECK(macro_calls == 2);
    NEAR(incoming_arguments[23], 20); NEAR(incoming_arguments[24], 8);
    CHECK(incoming_block("G67") == Status_OK && gc_state.g66_args == NULL);
    CHECK(incoming_block("G0X1") == Status_OK);
    CHECK(macro_calls == 2);
    return EXIT_SUCCESS;
}
