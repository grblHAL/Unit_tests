#pragma once
#include "support/motion_program_host.h"
static inline void prepare_rotated_arc(float degrees)
{
    prepare_motion_program();
    char command[64];
    snprintf(command, sizeof(command), "G10L2P2R%g", (double)degrees);
    CHECK(gc_execute_block(command) == Status_OK);
}
static inline void check_rotated_arc_endpoint(int32_t x, int32_t y, int32_t z)
{
    execute_motion_program();
    const int32_t expected[N_AXIS] = {x, y, z};
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == expected[axis]);
        CHECK(physical_position[axis] == expected[axis]);
        CHECK(axis_pulses[axis] == (unsigned)labs(expected[axis]));
    }
}
