#include "support/spindle_multi_override_host.h"
int main(void)
{
    prepare_independent_spindle_overrides();
    CHECK(spindle_program_block("M49") == Status_OK);
    check_independent_spindle_override_outputs(3000, 8400);
    CHECK(gc_state.modal.override_ctrl.feed_rates_disable);
    CHECK(spindle_get(0)->param->state.override_disable && !spindle_get(1)->param->state.override_disable);
    return EXIT_SUCCESS;
}
