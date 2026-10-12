#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    grbl.tool_table.n_tools = 1;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        gc_state.modal.tool_length_offset[axis] = axis + 1;
        gc_state.tool->offset.values[axis] = axis + 4;
    }
    gc_set_tool_offset(ToolLengthOffset_Cancel, Z_AXIS, 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        NEAR(gc_state.modal.tool_length_offset[axis], 0);
        NEAR(gc_state.tool->offset.values[axis], axis + 4);
    }
    return EXIT_SUCCESS;
}
