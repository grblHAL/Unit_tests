#pragma once
#include "support/engine_host.h"
#include "check.h"
static inline void prepare_parser_rejection(void)
{
    engine_parser_prepare();
    char initial[] = "G90G21G0X2Y3Z4";
    CHECK(gc_execute_block(initial) == Status_OK);
    char offset[] = "G43.1Z1";
    CHECK(gc_execute_block(offset) == Status_OK);
}
static inline void check_rejection_preserved_coordinates(void)
{
    CHECK(!gc_state.modal.units_imperial);
    CHECK(!gc_state.modal.distance_incremental);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_EnableDynamic);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 1);
    NEAR(gc_state.position[X_AXIS], 2);
    NEAR(gc_state.position[Y_AXIS], 3);
    NEAR(gc_state.position[Z_AXIS], 4);
    CHECK(plan_get_current_block() == NULL);
}
