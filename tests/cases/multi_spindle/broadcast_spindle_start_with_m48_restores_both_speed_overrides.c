#include "support/spindle_multi_override_host.h"
int main(void)
{
    prepare_independent_spindle_overrides();
    CHECK(spindle_program_block("M49") == Status_OK);
    CHECK(spindle_program_block("M51P0$1") == Status_OK);
    check_independent_spindle_override_outputs(3000, 7000);
    CHECK(spindle_program_block("M3M48$-1") == Status_OK);
    CHECK(!gc_state.modal.override_ctrl.feed_rates_disable);
    CHECK(spindle_get(0)->param->override_pct == 110 && spindle_get(1)->param->override_pct == 120);
    for(unsigned id = 0; id < 2; id++) CHECK(actual_spindle_states[id].on && !actual_spindle_states[id].ccw);
    CHECK(spindle_output_calls[2] == 0);
    fprintf(stderr, "Broadcast M48 disabled=%u,%u RPM=%g,%g expected=3300,8400\n",
        spindle_get(0)->param->state.override_disable, spindle_get(1)->param->state.override_disable,
        actual_spindle_rpm[0], actual_spindle_rpm[1]);
    CHECK(!spindle_get(0)->param->state.override_disable && !spindle_get(1)->param->state.override_disable);
    CHECK(fabsf(actual_spindle_rpm[0] - 3300) < .01f && fabsf(actual_spindle_rpm[1] - 8400) < .01f);
    return EXIT_SUCCESS;
}
