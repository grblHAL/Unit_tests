#include "support/incoming_macro_host.h"
int main(void)
{
    prepare_incoming_macro();
    CHECK(incoming_block("G67") == Status_OK && gc_state.g66_args == NULL);
    CHECK(incoming_block("G66P100X12") == Status_OK);
    CHECK(incoming_block("G0X1") == Status_OK && macro_calls == 1);
    CHECK(incoming_block("G67") == Status_OK);
    CHECK(incoming_block("G0X2") == Status_OK && macro_calls == 1);
    CHECK(incoming_block("G66.1P101X5") == Status_OK && macro_calls == 2);
    CHECK(incoming_block("G67") == Status_OK && gc_state.g66_args == NULL);
    return EXIT_SUCCESS;
}
