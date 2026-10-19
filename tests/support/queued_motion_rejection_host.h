#pragma once
#include "support/motion_program_host.h"
static inline void check_rejected_block_preserves_queued_motion(const char *text, status_code_t expected)
{
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    char command[96];
    CHECK(strlen(text) < sizeof(command));
    strcpy(command, text);
    status_code_t actual = gc_execute_block(command);
    if(actual != expected)
        fprintf(stderr, "Rejected block '%s': status=%u expected=%u\n", text, (unsigned)actual, (unsigned)expected);
    CHECK(actual == expected);
    CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
    CHECK(gc_state.modal.motion == MotionMode_Linear);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMin);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 100);
    NEAR(gc_state.position[X_AXIS], 1);
    NEAR(gc_state.position[Y_AXIS], 0);
    NEAR(gc_state.position[Z_AXIS], 0);
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 80 && sys.position[X_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
}

static inline void reject_without_losing_queued_motion(const char *text, status_code_t expected)
{
    prepare_motion_program();
    queue_motion_program("G1X1F100");
    check_rejected_block_preserves_queued_motion(text, expected);
}
