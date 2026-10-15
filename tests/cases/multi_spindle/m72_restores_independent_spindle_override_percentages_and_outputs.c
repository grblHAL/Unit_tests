#include "support/multi_spindle_modal_host.h"
int main(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();
    spindle_set_override(spindle_get(0), 120); spindle_set_override(spindle_get(1), 80);
    CHECK(spindle_program_block("M70") == Status_OK);
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    spindle_set_override(spindle_get(0), 50); spindle_set_override(spindle_get(1), 150);
    CHECK(spindle_program_block("M72") == Status_OK);
    CHECK(spindle_get(0)->param->override_pct == 120 && spindle_get(1)->param->override_pct == 80);
    /* Match the existing RPM multiplication tolerance, not the coordinate tolerance. */
    CHECK(fabsf(actual_spindle_rpm[0] - 3600) < .01f);
    CHECK(fabsf(actual_spindle_rpm[1] - 5600) < .01f);
    CHECK(actual_spindle_states[0].on && actual_spindle_states[1].on);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
