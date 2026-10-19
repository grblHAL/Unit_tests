#include "support/incoming_macro_host.h"
int main(void)
{
    prepare_incoming_macro();
    CHECK(incoming_block("G66.1P100A1B2") == Status_OK);
    CHECK(macro_calls == 1 && active_modal_macro() == 100);
    CHECK(incoming_block("A10") == Status_OK);
    CHECK(macro_calls == 2);
    NEAR(incoming_arguments[0], 10); NEAR(incoming_arguments[1], 2);
    CHECK(incoming_block("B20") == Status_OK);
    CHECK(macro_calls == 3);
    NEAR(incoming_arguments[0], 10); NEAR(incoming_arguments[1], 20);
    CHECK(incoming_block("G67") == Status_OK && gc_state.g66_args == NULL);
    return EXIT_SUCCESS;
}
