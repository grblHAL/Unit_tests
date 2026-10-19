#include "support/incoming_macro_host.h"
int main(void)
{
    prepare_incoming_macro();
    CHECK(incoming_block("G66P100G66.1P101") == Status_GcodeModalGroupViolation);
    CHECK(gc_state.g66_args == NULL && macro_calls == 0);
    CHECK(incoming_block("G66P100") == Status_OK);
    CHECK(incoming_block("G66P101") == Status_OK);
    CHECK(active_modal_macro() == 101 && gc_state.g66_args->prev != NULL);
    CHECK(incoming_block("G67") == Status_OK && active_modal_macro() == 100);
    CHECK(incoming_block("G67") == Status_OK && gc_state.g66_args == NULL);
    return EXIT_SUCCESS;
}
