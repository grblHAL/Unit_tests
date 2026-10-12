#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    grbl.tool_table.n_tools = 1;
    for(unsigned axis = 0; axis < N_AXIS; axis++) gc_state.tool->offset.values[axis] = axis + 2;
    char block[] = "G43";
    CHECK(gc_execute_block(block) == Status_OK);
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(gc_state.modal.tool_length_offset[axis], axis + 2);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_Enable);
    return EXIT_SUCCESS;
}
