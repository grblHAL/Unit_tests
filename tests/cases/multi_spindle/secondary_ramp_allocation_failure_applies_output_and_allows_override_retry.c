#include "support/paired_pwm_override_host.h"
#include "support/tracked_malloc_host.h"

int main(void)
{
    prepare_paired_pwm_program();
    CHECK(spindle_program_block("M3S6000$0") == Status_OK);
    unsigned primary_calls = pair_calls[0];
    allocation_heap_reject = 1;
    observe_allocation_heap = true;
    status_code_t status = spindle_program_block("M3S8000$1");
    observe_allocation_heap = false;
    CHECK(status == Status_OK);
    CHECK(allocation_heap_calls == 1 && allocation_heap_failures == 1);
    spindle_ptrs_t *primary = spindle_get(0), *secondary = spindle_get(1);
    CHECK(actual_spindle_states[1].on);
    CHECK(pair_output[1] == pair_get_pwm(secondary, secondary->param->rpm_overridden));
    NEAR(secondary->param->rpm, 8000);
    CHECK(pair_calls[0] == primary_calls && actual_spindle_states[0].on);
    NEAR(primary->param->rpm, 6000);
    pair_calls[0] = pair_calls[1] = 0;
    float first_target = spindle_set_override(primary, 120);
    float second_target = spindle_set_override(secondary, 80);
    CHECK(fabsf(first_target - 7200) < .01f && fabsf(second_target - 6400) < .01f);
    CHECK(pair_calls[0] == 0 && pair_calls[1] == 0);
    advance_pair_override_tasks(10);
    CHECK(pair_output[0] == pair_get_pwm(primary, first_target));
    CHECK(pair_output[1] == pair_get_pwm(secondary, second_target));
    CHECK(pair_calls[0] > 1 && pair_calls[1] > 1);
    unsigned completed[2] = {pair_calls[0], pair_calls[1]};
    advance_pair_override_tasks(10);
    CHECK(pair_calls[0] == completed[0] && pair_calls[1] == completed[1]);
    CHECK(actual_spindle_states[0].on && actual_spindle_states[1].on);
    return EXIT_SUCCESS;
}
