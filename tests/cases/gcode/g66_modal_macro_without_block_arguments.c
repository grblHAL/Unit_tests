#include "support/incoming_macro_host.h"
int main(void)
{
    prepare_incoming_macro();
    CHECK(incoming_block("G66P100X12") == Status_OK);
    CHECK(incoming_block("G0X1") == Status_OK && macro_calls == 1);
    NEAR(incoming_arguments[23], 12);
    CHECK(incoming_block("G0X2") == Status_OK && macro_calls == 2);
    NEAR(incoming_arguments[23], 12);
    CHECK(incoming_block("G67") == Status_OK && gc_state.g66_args == NULL);
    return EXIT_SUCCESS;
}
