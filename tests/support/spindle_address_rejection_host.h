#pragma once
#include "support/multi_spindle_host.h"

static inline void check_running_spindles_reject_address(const char *command, status_code_t expected)
{
    prepare_multi_spindle_program();
    CHECK(spindle_enable(1) == 1);
    CHECK(spindle_program_block("M3S5000") == Status_OK);
    CHECK(spindle_program_block("M4S7000$1") == Status_OK);
    unsigned calls[2] = {spindle_output_calls[0], spindle_output_calls[1]};
    CHECK(spindle_program_block(command) == expected);
    CHECK(spindle_output_calls[0] == calls[0] && spindle_output_calls[1] == calls[1]);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    NEAR(actual_spindle_rpm[0], 5000);
    NEAR(actual_spindle_rpm[1], 7000);
    CHECK(spindle_program_block("M5$1") == Status_OK);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[1].on);
}
