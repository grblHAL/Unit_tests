#include "support/tool_offset_host.h"
#include "check.h"

int main(void)
{
    prepare_offset_tool();
    for(unsigned axis = 0; axis < N_AXIS; axis++) gc_state.modal.tool_length_offset[axis] = 10;
    char block[] = "G43.2H1";
    CHECK(gc_execute_block(block) == Status_OK);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        NEAR(gc_state.modal.tool_length_offset[axis], 12 + axis);
        NEAR(offset_tool.offset.values[axis], 2 + axis);
    }
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_ApplyAdditional);
    return EXIT_SUCCESS;
}
