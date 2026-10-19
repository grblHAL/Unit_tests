#include "support/incoming_macro_host.h"
int main(void)
{
    prepare_incoming_macro();
    CHECK(incoming_block("G66P100X12") == Status_OK);
    CHECK(incoming_block("G80") == Status_OK);
    CHECK(active_modal_macro() == 100 && gc_state.modal.motion == MotionMode_None);
    CHECK(incoming_block("G0X2") == Status_OK && macro_calls == 1);
    CHECK(incoming_block("G67") == Status_OK && gc_state.g66_args == NULL);
    CHECK(incoming_block("G66.1P101X5") == Status_OK);
    CHECK(incoming_block("G80") == Status_OK && active_modal_macro() == 101);
    CHECK(incoming_block("G67") == Status_OK && gc_state.g66_args == NULL);
    return EXIT_SUCCESS;
}
