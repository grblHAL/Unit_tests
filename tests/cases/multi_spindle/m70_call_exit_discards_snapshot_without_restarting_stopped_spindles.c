#include "support/multi_spindle_modal_host.h"
int main(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();
    int context;
    CHECK(ngc_call_push(&context));
    CHECK(spindle_program_block("M70") == Status_OK);
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    (void)ngc_call_pop();
    CHECK(ngc_call_level() == 0);
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[1].on);
    CHECK(ngc_modal_state_get() == NULL);
    return EXIT_SUCCESS;
}
