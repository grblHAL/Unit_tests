#include "support/paired_pwm_program_host.h"
#include "ngc_params.h"
int main(void)
{
    prepare_paired_pwm_program();
    CHECK(spindle_program_block("M3S3000$0") == Status_OK);
    CHECK(spindle_program_block("M4S7000$1") == Status_OK);
    int macro_context;
    CHECK(ngc_call_push(&macro_context));
    CHECK(spindle_program_block("M73") == Status_OK);
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    CHECK(pair_output[0] == 0 && pair_output[1] == 0);
    pair_calls[0] = pair_calls[1] = 0;
    (void)ngc_call_pop();
    CHECK(ngc_call_level() == 0 && ngc_modal_state_get() == NULL);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    const uint_fast16_t expected[] = {300, 700};
    for(unsigned id = 0; id < 2; id++) {
        CHECK(pair_output[id] == expected[id] && pair_calls[id] > 1);
        uint_fast16_t previous = 0;
        for(unsigned n = 0; n < pair_calls[id]; n++) {
            CHECK(pair_log[id][n] >= previous && pair_log[id][n] <= expected[id]);
            previous = pair_log[id][n];
        }
    }
    NEAR(spindle_get(0)->param->rpm, 3000);
    NEAR(spindle_get(1)->param->rpm, 7000);
    return EXIT_SUCCESS;
}
