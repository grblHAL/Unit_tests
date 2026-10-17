#pragma once
#include "support/paired_pwm_program_host.h"
static inline void prepare_paired_pwm_overrides(void)
{
    prepare_paired_pwm_program();
    CHECK(spindle_program_block("M3S6000$0") == Status_OK);
    CHECK(spindle_program_block("M3S8000$1") == Status_OK);
    pair_calls[0] = pair_calls[1] = 0;
}
static inline void advance_pair_override_tasks(unsigned turns)
{
    for(unsigned i = 0; i < turns; i++) {
        engine_ticks += DWELL_TIME_STEP;
        engine_execute_tasks(STATE_IDLE);
    }
}
