#include "support/paired_pwm_program_host.h"

int main(void)
{
    prepare_paired_pwm_program();
    CHECK(spindle_program_block("M3S3000$0") == Status_OK);
    CHECK(spindle_program_block("M4S7000$1") == Status_OK);
    CHECK(pair_output[0] == 300 && pair_output[1] == 700);
    pair_calls[0] = pair_calls[1] = 0;
    spindle_all_off(false);
    for(unsigned id = 0; id < 2; id++) {
        CHECK(pair_output[id] == 0 && pair_calls[id] > 1);
        CHECK(!actual_spindle_states[id].on);
        CHECK(spindle_get(id)->param->rpm == 0);
        CHECK(spindle_get(id)->param->rpm_overridden == 0);
        uint_fast16_t previous = id ? 700 : 300;
        for(unsigned n = 0; n < pair_calls[id]; n++) {
            CHECK(pair_log[id][n] <= previous);
            previous = pair_log[id][n];
        }
        CHECK(previous == 0);
    }
    CHECK(!spindle_is_on());
    return EXIT_SUCCESS;
}
