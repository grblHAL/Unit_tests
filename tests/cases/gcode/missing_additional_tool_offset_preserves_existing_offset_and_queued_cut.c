#include "support/motion_program_host.h"
#include "support/tool_offset_host.h"

int main(void)
{
    prepare_motion_program();
    original_get_tool = grbl.tool_table.get_tool;
    grbl.tool_table.get_tool = lookup_offset_tool;
    grbl.tool_table.n_tools = 1;
    offset_tool.offset = (coord_data_t){.x = 1, .y = 2, .z = 3};
    char dynamic[] = "G43.1Z2", missing[] = "G43.2H2", retry[] = "G43.2H1";
    CHECK(gc_execute_block(dynamic) == Status_OK);
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    CHECK(gc_execute_block(missing) == Status_GcodeIllegalToolTableEntry);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_EnableDynamic);
    NEAR(gc_state.modal.tool_length_offset[X_AXIS], 0);
    NEAR(gc_state.modal.tool_length_offset[Y_AXIS], 0);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 2);
    CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
    CHECK(gc_execute_block(retry) == Status_OK);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_ApplyAdditional);
    NEAR(gc_state.modal.tool_length_offset[X_AXIS], 1);
    NEAR(gc_state.modal.tool_length_offset[Y_AXIS], 2);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 5);
    CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(gc_state.tool->tool_id == 0 && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
