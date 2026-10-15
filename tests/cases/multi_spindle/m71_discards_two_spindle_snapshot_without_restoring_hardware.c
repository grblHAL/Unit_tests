#include "support/multi_spindle_modal_host.h"
int main(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();
    CHECK(spindle_program_block("M70") == Status_OK);
    CHECK(ngc_modal_state_get() != NULL);
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    unsigned primary_calls = spindle_output_calls[0], secondary_calls = spindle_output_calls[1];
    CHECK(spindle_program_block("M71") == Status_OK);
    CHECK(ngc_modal_state_get() == NULL);
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[1].on);
    CHECK(spindle_output_calls[0] == primary_calls && spindle_output_calls[1] == secondary_calls);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
