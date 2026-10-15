#include "support/multi_spindle_modal_host.h"
int main(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();
    spindle_set_override(spindle_get(0), 120); spindle_set_override(spindle_get(1), 80);
    CHECK(spindle_program_block("M51P0$1") == Status_OK);
    CHECK(spindle_program_block("M70") == Status_OK);
    CHECK(spindle_program_block("M51P1$1") == Status_OK);
    spindle_set_override(spindle_get(1), 60);
    CHECK(spindle_program_block("M72") == Status_OK);
    CHECK(!spindle_get(0)->param->state.override_disable && spindle_get(1)->param->state.override_disable);
    CHECK(gc_state.modal.override_ctrl.spindle_rpm_disable == 2);
    CHECK(fabsf(actual_spindle_rpm[0] - 3600) < .01f);
    NEAR(actual_spindle_rpm[1], 7000);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
