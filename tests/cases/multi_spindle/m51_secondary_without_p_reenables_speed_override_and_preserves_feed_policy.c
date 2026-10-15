#include "support/multi_spindle_modal_host.h"

int main(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();
    CHECK(spindle_program_block("M49") == Status_OK);
    CHECK(spindle_program_block("M51P0$1") == Status_OK);
    CHECK(spindle_program_block("M51$1") == Status_OK);
    CHECK(gc_state.modal.override_ctrl.feed_rates_disable);
    CHECK(gc_state.modal.override_ctrl.spindle_rpm_disable == 1);
    CHECK(spindle_get(0)->param->state.override_disable);
    CHECK(!spindle_get(1)->param->state.override_disable);
    return EXIT_SUCCESS;
}
