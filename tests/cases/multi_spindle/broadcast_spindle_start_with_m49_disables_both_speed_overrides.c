#include "support/spindle_multi_override_host.h"
int main(void)
{
    prepare_independent_spindle_overrides();
    CHECK(spindle_program_block("M3M49$-1") == Status_OK);
    CHECK(gc_state.modal.override_ctrl.feed_rates_disable);
    CHECK(spindle_get(0)->param->state.override_disable && spindle_get(1)->param->state.override_disable);
    CHECK(fabsf(actual_spindle_rpm[0] - 3000) < .01f);
    CHECK(fabsf(actual_spindle_rpm[1] - 7000) < .01f);
    CHECK(spindle_get(0)->param->override_pct == 110 && spindle_get(1)->param->override_pct == 120);
    for(unsigned id = 0; id < 2; id++) CHECK(actual_spindle_states[id].on && !actual_spindle_states[id].ccw);
    CHECK(spindle_output_calls[2] == 0);
    CHECK(spindle_program_block("M51P1$1") == Status_OK);
    CHECK(fabsf(actual_spindle_rpm[0] - 3000) < .01f);
    CHECK(fabsf(actual_spindle_rpm[1] - 8400) < .01f);
    CHECK(spindle_get(0)->param->state.override_disable && !spindle_get(1)->param->state.override_disable);
    CHECK(gc_state.modal.override_ctrl.feed_rates_disable && spindle_output_calls[2] == 0);
    return EXIT_SUCCESS;
}
