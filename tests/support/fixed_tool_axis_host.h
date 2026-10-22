#pragma once
#include "support/tool_change_host.h"
#if TOOL_LENGTH_OFFSET_AXIS < X_AXIS || TOOL_LENGTH_OFFSET_AXIS > Z_AXIS
#error This fixture requires a fixed X, Y or Z tool offset axis
#endif
static inline void run_fixed_axis_dynamic_offset(void)
{
    prepare_motion_program();
    char command[64];
    snprintf(command, sizeof(command), "G43.1%c2", *axis_letter[TOOL_LENGTH_OFFSET_AXIS]);
    CHECK(gc_execute_block(command) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset[TOOL_LENGTH_OFFSET_AXIS], 2);
    snprintf(command, sizeof(command), "G43.1%c9", TOOL_LENGTH_OFFSET_AXIS == Z_AXIS ? 'X' : 'Z');
    CHECK(gc_execute_block(command) == Status_GcodeG43DynamicAxisError);
    NEAR(gc_state.modal.tool_length_offset[TOOL_LENGTH_OFFSET_AXIS], 2);
    CHECK(plan_get_current_block() == NULL);
    snprintf(command, sizeof(command), "G1%c1F100", *axis_letter[TOOL_LENGTH_OFFSET_AXIS]);
    queue_motion_program(command);
    execute_motion_program();
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == (axis == TOOL_LENGTH_OFFSET_AXIS ? 240 : 0));
        CHECK(axis_pulses[axis] == (axis == TOOL_LENGTH_OFFSET_AXIS ? 240u : 0u));
    }
}
static inline void run_fixed_axis_manual_change(void)
{
    prepare_tool_change_motion();
    const int32_t original[N_AXIS] = {-160, -240, -80};
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        sys.position[axis] = physical_position[axis] = original[axis];
    sync_position();
    sys.homed.mask = AXES_BITMASK;
    install_manual_change_interface();
    char plane[] = "G18", change[] = "T3M6";
    CHECK(gc_execute_block(plane) == Status_OK);
    CHECK(gc_execute_block(change) == Status_OK);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(physical_position[axis] == (axis == TOOL_LENGTH_OFFSET_AXIS ? 0 : original[axis]));
    char touch[] = "G10L2P1X0Y0Z0";
    CHECK(gc_execute_block(touch) == Status_OK);
    grbl.on_toolchange_ack();
    CHECK(tool_stream_handler(CMD_CYCLE_START));
    engine_execute_tasks(STATE_TOOL_CHANGE);
    CHECK(protocol_execute_realtime());
    CHECK(!HOST_PARSER_FLAGS.tool_change && gc_state.tool->tool_id == 3);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(physical_position[axis] == original[axis]);
        CHECK(axis_pulses[axis] == (axis == TOOL_LENGTH_OFFSET_AXIS ? (unsigned)(-2 * original[axis]) : 0u));
    }
    CHECK(plan_get_current_block() == NULL);
}
