#pragma once
#include "support/multi_spindle_modal_host.h"
static inline void start_clockwise_broadcast_fixture(void)
{
    prepare_multi_spindle_modal_program();
    CHECK(spindle_program_block("M3S3000$0") == Status_OK);
    CHECK(spindle_program_block("M3S7000$1") == Status_OK);
}
static inline void check_broadcast_outputs(bool ccw)
{
    for(unsigned i = 0; i < 2; i++) CHECK(actual_spindle_states[i].on && actual_spindle_states[i].ccw == ccw);
    NEAR(actual_spindle_rpm[0], 3000); NEAR(actual_spindle_rpm[1], 7000);
    NEAR(gc_state.modal.spindle[0].rpm, 3000); NEAR(gc_state.modal.spindle[1].rpm, 7000);
    CHECK(spindle_output_calls[2] == 0 && !spindle_is_enabled(2));
}
static inline void check_rejected_broadcast(const char *command, status_code_t expected)
{
    unsigned before0 = spindle_output_calls[0], before1 = spindle_output_calls[1];
    CHECK(spindle_program_block(command) == expected);
    CHECK(spindle_output_calls[0] == before0 && spindle_output_calls[1] == before1);
    check_broadcast_outputs(false);
}
