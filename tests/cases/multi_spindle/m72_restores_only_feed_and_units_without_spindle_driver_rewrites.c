#include "support/multi_spindle_modal_host.h"
int main(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();
    CHECK(spindle_program_block("G21G90F120") == Status_OK);
    CHECK(spindle_program_block("M70") == Status_OK);
    unsigned calls0 = spindle_output_calls[0], calls1 = spindle_output_calls[1];
    CHECK(spindle_program_block("G20G91F2") == Status_OK);
    CHECK(spindle_program_block("M72") == Status_OK);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 120);
    CHECK(spindle_output_calls[0] == calls0 && spindle_output_calls[1] == calls1);
    NEAR(actual_spindle_rpm[0], 3000); NEAR(actual_spindle_rpm[1], 7000);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
